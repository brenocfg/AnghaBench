#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  void Udata ;

/* Variables and functions */
 int /*<<< orphan*/  api_incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  getcurrenv (TYPE_1__*) ; 
 int /*<<< orphan*/  luaC_checkGC (TYPE_1__*) ; 
 void* luaS_newudata (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setuvalue (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void*lua_newuserdata(lua_State*L,size_t size){
Udata*u;
luaC_checkGC(L);
u=luaS_newudata(L,size,getcurrenv(L));
setuvalue(L,L->top,u);
api_incr_top(L);
return u+1;
}