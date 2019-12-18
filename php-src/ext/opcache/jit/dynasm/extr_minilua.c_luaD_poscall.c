#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ top; int /*<<< orphan*/  savedpc; int /*<<< orphan*/  base; int /*<<< orphan*/  ci; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_6__ {scalar_t__ func; int nresults; int /*<<< orphan*/  savedpc; int /*<<< orphan*/  base; } ;
typedef  scalar_t__ StkId ;
typedef  TYPE_2__ CallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  setnilvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int luaD_poscall(lua_State*L,StkId firstResult){
StkId res;
int wanted,i;
CallInfo*ci;
ci=L->ci--;
res=ci->func;
wanted=ci->nresults;
L->base=(ci-1)->base;
L->savedpc=(ci-1)->savedpc;
for(i=wanted;i!=0&&firstResult<L->top;i--)
setobj(L,res++,firstResult++);
while(i-->0)
setnilvalue(res++);
L->top=res;
return(wanted-(-1));
}