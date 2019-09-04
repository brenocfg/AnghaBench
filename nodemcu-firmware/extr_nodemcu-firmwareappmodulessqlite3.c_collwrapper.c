#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ref; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ scc ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int collwrapper(scc *co,int l1,const void *p1,
                        int l2,const void *p2) {
    int res=0;
    lua_State *L=co->L;
    lua_rawgeti(L,LUA_REGISTRYINDEX,co->ref);
    lua_pushlstring(L,p1,l1);
    lua_pushlstring(L,p2,l2);
    if (lua_pcall(L,2,1,0)==0) res=(int)lua_tonumber(L,-1);
    lua_pop(L,1);
    return res;
}