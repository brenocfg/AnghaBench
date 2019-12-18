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
struct TYPE_3__ {scalar_t__ self_ref; int mode; int /*<<< orphan*/  os; } ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 scalar_t__ LUA_REFNIL ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int TIMER_IDLE_FLAG ; 
 int TIMER_MODE_OFF ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 TYPE_1__* tmr_get (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tmr_stop(lua_State* L){
	tmr_t tmr = tmr_get(L, 1);

	if (tmr->self_ref != LUA_REFNIL) {
		luaL_unref(L, LUA_REGISTRYINDEX, tmr->self_ref);
		tmr->self_ref = LUA_NOREF;
	}

	//we return false if the timer is idle (of not registered)
	if(!(tmr->mode & TIMER_IDLE_FLAG) && tmr->mode != TIMER_MODE_OFF){
		tmr->mode |= TIMER_IDLE_FLAG;
		os_timer_disarm(&tmr->os);
		lua_pushboolean(L, 1);
	}else{
		lua_pushboolean(L, 0);
	}
	return 1;
}