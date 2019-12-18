#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int info; } ;
struct TYPE_29__ {TYPE_3__ s; } ;
struct TYPE_30__ {scalar_t__ k; TYPE_4__ u; } ;
typedef  TYPE_5__ expdesc ;
struct TYPE_32__ {int freereg; } ;
struct TYPE_26__ {int /*<<< orphan*/  ts; } ;
struct TYPE_27__ {int token; TYPE_1__ seminfo; } ;
struct TYPE_31__ {int linenumber; int lastline; TYPE_2__ t; TYPE_7__* fs; } ;
typedef  TYPE_6__ LexState ;
typedef  TYPE_7__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  OP_CALL ; 
#define  TK_STRING 128 
 int /*<<< orphan*/  VCALL ; 
 scalar_t__ VVOID ; 
 int /*<<< orphan*/  check_match (TYPE_6__*,char,char,int) ; 
 int /*<<< orphan*/  codestring (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constructor (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  explist1 (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ hasmultret (scalar_t__) ; 
 int /*<<< orphan*/  init_exp (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_codeABC (TYPE_7__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  luaK_fixline (TYPE_7__*,int) ; 
 int /*<<< orphan*/  luaK_setmultret (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  luaX_next (TYPE_6__*) ; 
 int /*<<< orphan*/  luaX_syntaxerror (TYPE_6__*,char*) ; 

__attribute__((used)) static void funcargs(LexState*ls,expdesc*f){
FuncState*fs=ls->fs;
expdesc args;
int base,nparams;
int line=ls->linenumber;
switch(ls->t.token){
case'(':{
if(line!=ls->lastline)
luaX_syntaxerror(ls,"ambiguous syntax (function call x new statement)");
luaX_next(ls);
if(ls->t.token==')')
args.k=VVOID;
else{
explist1(ls,&args);
luaK_setmultret(fs,&args);
}
check_match(ls,')','(',line);
break;
}
case'{':{
constructor(ls,&args);
break;
}
case TK_STRING:{
codestring(ls,&args,ls->t.seminfo.ts);
luaX_next(ls);
break;
}
default:{
luaX_syntaxerror(ls,"function arguments expected");
return;
}
}
base=f->u.s.info;
if(hasmultret(args.k))
nparams=(-1);
else{
if(args.k!=VVOID)
luaK_exp2nextreg(fs,&args);
nparams=fs->freereg-(base+1);
}
init_exp(f,VCALL,luaK_codeABC(fs,OP_CALL,base,nparams+1,2));
luaK_fixline(fs,line);
fs->freereg=base+1;
}