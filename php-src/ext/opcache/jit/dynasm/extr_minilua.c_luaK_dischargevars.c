#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* aux; void* info; } ;
struct TYPE_7__ {TYPE_1__ s; } ;
struct TYPE_8__ {int k; TYPE_2__ u; } ;
typedef  TYPE_3__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  OP_GETGLOBAL ; 
 int /*<<< orphan*/  OP_GETTABLE ; 
 int /*<<< orphan*/  OP_GETUPVAL ; 
#define  VCALL 133 
#define  VGLOBAL 132 
#define  VINDEXED 131 
#define  VLOCAL 130 
 int VNONRELOC ; 
 void* VRELOCABLE ; 
#define  VUPVAL 129 
#define  VVARARG 128 
 int /*<<< orphan*/  freereg (int /*<<< orphan*/ *,void*) ; 
 void* luaK_codeABC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 void* luaK_codeABx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  luaK_setoneret (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void luaK_dischargevars(FuncState*fs,expdesc*e){
switch(e->k){
case VLOCAL:{
e->k=VNONRELOC;
break;
}
case VUPVAL:{
e->u.s.info=luaK_codeABC(fs,OP_GETUPVAL,0,e->u.s.info,0);
e->k=VRELOCABLE;
break;
}
case VGLOBAL:{
e->u.s.info=luaK_codeABx(fs,OP_GETGLOBAL,0,e->u.s.info);
e->k=VRELOCABLE;
break;
}
case VINDEXED:{
freereg(fs,e->u.s.aux);
freereg(fs,e->u.s.info);
e->u.s.info=luaK_codeABC(fs,OP_GETTABLE,0,e->u.s.info,e->u.s.aux);
e->k=VRELOCABLE;
break;
}
case VVARARG:
case VCALL:{
luaK_setoneret(fs,e);
break;
}
default:break;
}
}