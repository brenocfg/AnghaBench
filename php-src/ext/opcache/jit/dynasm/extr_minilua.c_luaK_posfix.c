#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  info; } ;
struct TYPE_16__ {TYPE_1__ s; } ;
struct TYPE_17__ {TYPE_2__ u; int /*<<< orphan*/  k; int /*<<< orphan*/  t; int /*<<< orphan*/  f; } ;
typedef  TYPE_3__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int BinOpr ;

/* Variables and functions */
 int /*<<< orphan*/  GET_OPCODE (int /*<<< orphan*/ ) ; 
#define  OPR_ADD 142 
#define  OPR_AND 141 
#define  OPR_CONCAT 140 
#define  OPR_DIV 139 
#define  OPR_EQ 138 
#define  OPR_GE 137 
#define  OPR_GT 136 
#define  OPR_LE 135 
#define  OPR_LT 134 
#define  OPR_MOD 133 
#define  OPR_MUL 132 
#define  OPR_NE 131 
#define  OPR_OR 130 
#define  OPR_POW 129 
#define  OPR_SUB 128 
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  OP_CONCAT ; 
 int /*<<< orphan*/  OP_DIV ; 
 int /*<<< orphan*/  OP_EQ ; 
 int /*<<< orphan*/  OP_LE ; 
 int /*<<< orphan*/  OP_LT ; 
 int /*<<< orphan*/  OP_MOD ; 
 int /*<<< orphan*/  OP_MUL ; 
 int /*<<< orphan*/  OP_POW ; 
 int /*<<< orphan*/  OP_SUB ; 
 int /*<<< orphan*/  SETARG_B (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VRELOCABLE ; 
 int /*<<< orphan*/  codearith (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  codecomp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  freeexp (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  getcode (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_dischargevars (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_exp2val (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void luaK_posfix(FuncState*fs,BinOpr op,expdesc*e1,expdesc*e2){
switch(op){
case OPR_AND:{
luaK_dischargevars(fs,e2);
luaK_concat(fs,&e2->f,e1->f);
*e1=*e2;
break;
}
case OPR_OR:{
luaK_dischargevars(fs,e2);
luaK_concat(fs,&e2->t,e1->t);
*e1=*e2;
break;
}
case OPR_CONCAT:{
luaK_exp2val(fs,e2);
if(e2->k==VRELOCABLE&&GET_OPCODE(getcode(fs,e2))==OP_CONCAT){
freeexp(fs,e1);
SETARG_B(getcode(fs,e2),e1->u.s.info);
e1->k=VRELOCABLE;e1->u.s.info=e2->u.s.info;
}
else{
luaK_exp2nextreg(fs,e2);
codearith(fs,OP_CONCAT,e1,e2);
}
break;
}
case OPR_ADD:codearith(fs,OP_ADD,e1,e2);break;
case OPR_SUB:codearith(fs,OP_SUB,e1,e2);break;
case OPR_MUL:codearith(fs,OP_MUL,e1,e2);break;
case OPR_DIV:codearith(fs,OP_DIV,e1,e2);break;
case OPR_MOD:codearith(fs,OP_MOD,e1,e2);break;
case OPR_POW:codearith(fs,OP_POW,e1,e2);break;
case OPR_EQ:codecomp(fs,OP_EQ,1,e1,e2);break;
case OPR_NE:codecomp(fs,OP_EQ,0,e1,e2);break;
case OPR_LT:codecomp(fs,OP_LT,1,e1,e2);break;
case OPR_LE:codecomp(fs,OP_LE,1,e1,e2);break;
case OPR_GT:codecomp(fs,OP_LT,0,e1,e2);break;
case OPR_GE:codecomp(fs,OP_LE,0,e1,e2);break;
default:;
}
}