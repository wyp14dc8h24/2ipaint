#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define X 78
#define Y 21

void clear(){printf("\033c");}
void help(int brushcolor){
  printf("\
2iPaint Disc-8 & Halcyon Software 2022(C).                  Current color: \e[48;5;%dm %d \e[0m\n\
WSAD & HJKL to move cursor, P and R to toggle drawing. Colors:|",brushcolor,brushcolor);
for(int i=0;i<8;++i)printf("\e[48;5;%dm%2d",i,i);
printf("\e[0m\nC and M to select color (input), E to exit and export as ANBM.|");
for(int i=0;i<8;++i)printf("\e[48;5;%dm%2d",i+8,i+8);
printf("\e[0m");
}
void export(int file[Y][X]){
printf("int anbm[%d][%d]={",Y,X);
 for(int y=0;y<Y;++y){printf("{"); // motherfucker
  for(int x=0;x<X;++x){printf("%d",file[y][x]);
  if(x!=X-1)printf(",");}
 printf("}");if(y!=Y-1)printf(",");else printf("};");printf("\n");}
}

int main(int argc,char **argv[]){
  struct termios bezentertermios,zwyklytermios;
  tcgetattr(STDIN_FILENO,&zwyklytermios);bezentertermios=zwyklytermios;
  bezentertermios.c_lflag&=~(ICANON);
  tcsetattr(STDIN_FILENO,TCSANOW,&bezentertermios);

 int grid[Y][X]={0},
     curx=X/2,
     cury=Y/2,
     brushcolor=15,
     drawing=0;
 char input;
 
 while(1){
  clear();
  if(drawing==1)grid[cury][curx]=brushcolor;

  printf("/[2uiPaint");for(int i=0;i<X-13;++i)printf("=");printf("135=\\\n");
  for(int y=0;y<Y;++y){ printf("I");
   for(int x=0;x<X;++x){
    printf("\e[48;5;%dm",grid[y][x]);
    if(y==cury&&x==curx)printf("X");else printf(" ");
   }
  printf("\e[0mI\n");
  }
  printf("\\");for(int i=0;i<X;++i)printf("=");printf("/\n");
  help(brushcolor);

  scanf("%c",&input);
  switch(input){
   case 'w':case 'k':if(cury!=0)cury--;break;
   case 's':case 'j':if(cury!=Y)cury++;break;
   case 'a':case 'h':if(curx!=0)curx--;break;
   case 'd':case 'l':if(curx!=X)curx++;break;
   case 'p':case 'r':if(drawing==0)drawing=1;else drawing=0;break;
   case 'e':clear();export(grid);return 0;break;
   case 'c':case 'm':
  printf("Select Color.> ");
  tcsetattr(STDIN_FILENO,TCSANOW,&zwyklytermios);
   scanf("%d",&brushcolor);
  tcsetattr(STDIN_FILENO,TCSANOW,&bezentertermios);break;
  }
 }
 tcsetattr(STDIN_FILENO,TCSANOW,&zwyklytermios);
}
