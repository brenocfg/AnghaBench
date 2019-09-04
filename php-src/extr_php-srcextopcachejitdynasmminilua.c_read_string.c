#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int current; int /*<<< orphan*/  buff; } ;
struct TYPE_11__ {int /*<<< orphan*/  ts; } ;
typedef  TYPE_1__ SemInfo ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  TK_EOS ; 
 int /*<<< orphan*/  TK_STRING ; 
 int UCHAR_MAX ; 
 int /*<<< orphan*/  inclinenumber (TYPE_2__*) ; 
 int /*<<< orphan*/  isdigit (int) ; 
 int /*<<< orphan*/  luaX_lexerror (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaX_newstring (TYPE_2__*,scalar_t__,scalar_t__) ; 
 scalar_t__ luaZ_buffer (int /*<<< orphan*/ ) ; 
 scalar_t__ luaZ_bufflen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next (TYPE_2__*) ; 
 int /*<<< orphan*/  save (TYPE_2__*,int) ; 
 int /*<<< orphan*/  save_and_next (TYPE_2__*) ; 

__attribute__((used)) static void read_string(LexState*ls,int del,SemInfo*seminfo){
save_and_next(ls);
while(ls->current!=del){
switch(ls->current){
case(-1):
luaX_lexerror(ls,"unfinished string",TK_EOS);
continue;
case'\n':
case'\r':
luaX_lexerror(ls,"unfinished string",TK_STRING);
continue;
case'\\':{
int c;
next(ls);
switch(ls->current){
case'a':c='\a';break;
case'b':c='\b';break;
case'f':c='\f';break;
case'n':c='\n';break;
case'r':c='\r';break;
case't':c='\t';break;
case'v':c='\v';break;
case'\n':
case'\r':save(ls,'\n');inclinenumber(ls);continue;
case(-1):continue;
default:{
if(!isdigit(ls->current))
save_and_next(ls);
else{
int i=0;
c=0;
do{
c=10*c+(ls->current-'0');
next(ls);
}while(++i<3&&isdigit(ls->current));
if(c>UCHAR_MAX)
luaX_lexerror(ls,"escape sequence too large",TK_STRING);
save(ls,c);
}
continue;
}
}
save(ls,c);
next(ls);
continue;
}
default:
save_and_next(ls);
}
}
save_and_next(ls);
seminfo->ts=luaX_newstring(ls,luaZ_buffer(ls->buff)+1,
luaZ_bufflen(ls->buff)-2);
}