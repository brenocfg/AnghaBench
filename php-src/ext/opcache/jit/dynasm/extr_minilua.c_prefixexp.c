#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_9__ {int token; } ;
struct TYPE_10__ {int linenumber; int /*<<< orphan*/  fs; TYPE_1__ t; } ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
#define  TK_NAME 128 
 int /*<<< orphan*/  check_match (TYPE_2__*,char,char,int) ; 
 int /*<<< orphan*/  expr (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_dischargevars (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaX_next (TYPE_2__*) ; 
 int /*<<< orphan*/  luaX_syntaxerror (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  singlevar (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prefixexp(LexState*ls,expdesc*v){
switch(ls->t.token){
case'(':{
int line=ls->linenumber;
luaX_next(ls);
expr(ls,v);
check_match(ls,')','(',line);
luaK_dischargevars(ls->fs,v);
return;
}
case TK_NAME:{
singlevar(ls,v);
return;
}
default:{
luaX_syntaxerror(ls,"unexpected symbol");
return;
}
}
}