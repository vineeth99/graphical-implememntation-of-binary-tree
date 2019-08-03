#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#define MAX 20
int i=0;
void display();
struct node
{
  char s[2];
  int x;
  int y;
  int r;
  int w;
  int c;
  struct node *lc;
  struct node *rc;
}*root=NULL;
struct node *stack[MAX],*stackd[MAX],*stackl[MAX];
int topd=-1,topl=-1,top=-1;
void push(struct node *temp)
{
  if(top==MAX-1)
     return;
  else
     stack[++top]=temp;
}
struct node * pop()
{
  if(top==-1)
     return NULL;
  else
     return(stack[top--]);
}
void pushl(struct node *temp)
{
  if(topl==MAX-1)
     return;
  else
     stackl[++topl]=temp;
}
struct node * popl()
{
  if(topl==-1)
     return NULL;
  else
     return(stackl[topl--]);
}
void pushd(struct node *temp)
{
  if(topd==MAX-1)
     return;
  else
     stackd[++topd]=temp;
}
struct node * popd()
{
  if(topd==-1)
     return NULL;
  else
     return(stackd[topd--]);
}
void create()
{
  int gd=DETECT,gm,j=1;
  struct node *nn,*temp;
  char ch;
  int x1,y1,r1,w1;
  initgraph(&gd,&gm,"C:\\TC\\BGI");
  x1=getmaxx()/2;
  y1=30;
  r1=30;
  w1=4;
  closegraph();
  nn=(struct node *)malloc(sizeof(struct node));
  printf("Enter the root node\n");
  scanf("%s",&nn->s);
  nn->x=x1;
  nn->y=y1;
  nn->r=r1;
  nn->w=w1;
  nn->c=j;
  pushd(nn);
  display();
  root=nn;
  temp=root;
  while(temp!=NULL)
  {
  j++;
  printf("Do you want to create the left node of %s\n",temp->s);
  fflush(stdin);
  scanf("%c",&ch);
  if(ch=='y'||ch=='Y')
  {
     nn=(struct node *)malloc(sizeof(struct node));
     printf("enter the data\n");
     fflush(stdin);
     scanf("%s",&nn->s);
     nn->x=x1-w1*r1;
     nn->y=y1+w1*r1;
     nn->r=r1-w1;
     nn->w=w1-1;
     nn->c=j;
     temp->lc=nn;
     pushd(nn);
     display();
  }
  else
  {
     temp->lc=NULL;
     display();
  }
  printf("Do you want to create the right node of %s\n",temp->s);
  fflush(stdin);
  scanf("%c",&ch);
  if(ch=='y'||ch=='Y')
  {
    nn=(struct node *)malloc(sizeof(struct node));
    printf("enter the data\n");
    fflush(stdin);
    scanf("%s",&nn->s);
    nn->x=x1+w1*r1;
     nn->y=y1+w1*r1;
     nn->r=r1-w1;
     nn->w=w1-1;
     nn->c=j;
    temp->rc=nn;
    push(nn);
    pushd(nn);
    display();
  }
  else
  {
     temp->rc=NULL;
     display();
  }
  if(temp->lc==NULL)
  {
      temp=pop();
      j=temp->c;
  }
  else
      temp=temp->lc;
  x1=temp->x;
  y1=temp->y;
  r1=temp->r;
  w1=temp->w;
  if(w1==0)
     w1=1;
  }
}
void display()
{
   int gd=DETECT,gm,j=0,x1,y1,x2,y2;
   struct node *temp;
   initgraph(&gd,&gm,"C:\\TC\\BGI");
   pushd(NULL);
   temp=stackd[j];
   j++;
   while(temp!=NULL)
   {
      setcolor(12);
      setfillstyle(SOLID_FILL,temp->c);
      circle(temp->x,temp->y,temp->r);
      floodfill(temp->x,temp->y,12);
      outtextxy(temp->x,temp->y,temp->s);
      temp=stackd[j];
      j++;
   }
   temp=popd();
   x1=getmaxx()-30;
   y1=0;
   x2=getmaxx();
   y2=getmaxy();
   rectangle(x1,y1,x2,y2);
   y2=y2-30;
   while(y2>0)
   {
     line(x1,y2,x2,y2);
     y2=y2-30;
   }
   y2=getmaxy();
   y1=getmaxy()-30;
   push(NULL);
   j=0;
   temp=stack[j];
   while(temp!=NULL)
   {
     outtextxy((x1+x2)/2,(y1+y2)/2,temp->s);
     y1-=30;
     y2-=30;
     temp=stack[++j];
   }
   temp=pop();
   temp=root;
   if(i==1)
   {
   while(temp!=NULL)
   {
     if(temp->lc!=NULL)
       line(temp->x-temp->r,temp->y+temp->r,temp->lc->x+temp->lc->r,temp->lc->y-temp->lc->r);
     if(temp->rc!=NULL)
     {
       line(temp->x+temp->r,temp->y+temp->r,temp->rc->x-temp->rc->r,temp->rc->y-temp->rc->r);
       pushl(temp->rc);
     }
     if(temp->lc==NULL)
	temp=popl();
     else
	temp=temp->lc;
   }
   }
   delay(1500);
   closegraph();
}
void menu()
{
   int gd=DETECT,gm,x,y,z,w;
   initgraph(&gd,&gm,"C:\\TC\\BGI");
   setbkcolor(5);
   x=5;
   y=5;
   w=getmaxx()-5;
   z=getmaxy()-5;
   rectangle(x,y,w,z);
   outtextxy(x+10,y+10,"Create a binary tree");
   outtextxy(x+10,y+30,"Display the binary tree");
   outtextxy(x+10,y+50,"Exit");
   outtextxy(x+15,z-15,"Use up and down arrow keys to navigate");
   outtextxy(x+355,z-15,"Press right arrow keys to select");
   rectangle(x+5,y+5+i*20,x+200,y+20+i*20);
}
void operation()
{
  if(i==0)
     create();
  else if(i==1)
     display();
  else
     i=-1;
}
void main()
{
 int ch;
 char c;
 clrscr();
 do
 {
     menu();
     ch=getch();
   if(ch==0||ch==224)
   {
     switch(getch())
     {
       case 72:
	       if(i==0)
		  break;
	       else
		  i--;
	       break;
       case 80:
	       if(i==2)
		  break;
	       else
		  i++;
	       break;
       case 77:
	       closegraph();
	       operation();
	       break;
     }
   }
 }while(i!=-1);
}