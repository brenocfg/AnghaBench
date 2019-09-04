#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int info; } ;
struct TYPE_16__ {TYPE_2__ s; } ;
struct TYPE_18__ {int /*<<< orphan*/  k; TYPE_1__ u; } ;
typedef  TYPE_3__ expdesc ;
struct TYPE_19__ {int freereg; } ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  OP_SELF ; 
 int /*<<< orphan*/  VNONRELOC ; 
 int /*<<< orphan*/  freeexp (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_codeABC (TYPE_4__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_exp2RK (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_exp2anyreg (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_reserveregs (TYPE_4__*,int) ; 

__attribute__((used)) static void luaK_self(FuncState*fs,expdesc*e,expdesc*key){
int func;
luaK_exp2anyreg(fs,e);
freeexp(fs,e);
func=fs->freereg;
luaK_reserveregs(fs,2);
luaK_codeABC(fs,OP_SELF,func,e->u.s.info,luaK_exp2RK(fs,key));
freeexp(fs,key);
e->u.s.info=func;
e->k=VNONRELOC;
}