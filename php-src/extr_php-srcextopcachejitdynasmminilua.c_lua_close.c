#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ baseCcalls; scalar_t__ nCcalls; TYPE_1__* ci; int /*<<< orphan*/  top; int /*<<< orphan*/  base; TYPE_1__* base_ci; scalar_t__ errfunc; int /*<<< orphan*/  stack; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_12__ {TYPE_2__* mainthread; } ;
struct TYPE_10__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_8__* G (TYPE_2__*) ; 
 int /*<<< orphan*/  callallgcTM ; 
 int /*<<< orphan*/  close_state (TYPE_2__*) ; 
 int /*<<< orphan*/  luaC_separateudata (TYPE_2__*,int) ; 
 scalar_t__ luaD_rawrunprotected (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaF_close (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lua_close(lua_State*L){
L=G(L)->mainthread;
luaF_close(L,L->stack);
luaC_separateudata(L,1);
L->errfunc=0;
do{
L->ci=L->base_ci;
L->base=L->top=L->ci->base;
L->nCcalls=L->baseCcalls=0;
}while(luaD_rawrunprotected(L,callallgcTM,NULL)!=0);
close_state(L);
}