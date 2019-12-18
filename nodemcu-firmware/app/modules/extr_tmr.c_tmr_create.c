#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* tmr_t ;
typedef  int /*<<< orphan*/  timer_struct_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  os; int /*<<< orphan*/  mode; void* self_ref; void* lua_ref; } ;

/* Variables and functions */
 void* LUA_NOREF ; 
 int /*<<< orphan*/  TIMER_MODE_OFF ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tmr_create( lua_State *L ) {
	tmr_t ud = (tmr_t)lua_newuserdata(L, sizeof(timer_struct_t));
	if (!ud) return luaL_error(L, "not enough memory");
	luaL_getmetatable(L, "tmr.timer");
	lua_setmetatable(L, -2);
	ud->lua_ref = LUA_NOREF;
	ud->self_ref = LUA_NOREF;
	ud->mode = TIMER_MODE_OFF;
	os_timer_disarm(&ud->os);
	return 1;
}