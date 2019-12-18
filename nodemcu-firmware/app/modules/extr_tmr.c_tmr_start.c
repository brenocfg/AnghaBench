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
typedef  TYPE_1__* tmr_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {scalar_t__ self_ref; int mode; int /*<<< orphan*/  interval; int /*<<< orphan*/  os; } ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int TIMER_IDLE_FLAG ; 
 int TIMER_MODE_AUTO ; 
 scalar_t__ luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* tmr_get (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tmr_start(lua_State* L){
	tmr_t tmr = tmr_get(L, 1);

	if (tmr->self_ref == LUA_NOREF) {
		lua_pushvalue(L, 1);
		tmr->self_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	//we return false if the timer is not idle
	if(!(tmr->mode&TIMER_IDLE_FLAG)){
		lua_pushboolean(L, 0);
	}else{
		tmr->mode &= ~TIMER_IDLE_FLAG;
		os_timer_arm(&tmr->os, tmr->interval, tmr->mode==TIMER_MODE_AUTO);
		lua_pushboolean(L, 1);
	}
	return 1;
}