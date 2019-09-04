#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  os_timer_func_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 scalar_t__ LUA_TLIGHTFUNCTION ; 
 int /*<<< orphan*/  TCS34725_ENABLE ; 
 int /*<<< orphan*/  TCS34725_ENABLE_PON ; 
 int /*<<< orphan*/  TCS34725_EN_DELAY ; 
 scalar_t__ cb_tcs_en ; 
 int /*<<< orphan*/  dbg_printf (char*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tcs34725EnableDone ; 
 int /*<<< orphan*/  tcs34725Write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcs34725_timer ; 

uint8_t tcs34725Enable(lua_State* L)
{
	dbg_printf("Enable begun\n");

	if (lua_type(L, 1) == LUA_TFUNCTION || lua_type(L, 1) == LUA_TLIGHTFUNCTION) {
		if (cb_tcs_en != LUA_NOREF) {
			luaL_unref(L, LUA_REGISTRYINDEX, cb_tcs_en);
		}
		lua_pushvalue(L, 1);
		cb_tcs_en = luaL_ref(L, LUA_REGISTRYINDEX);
	} else {
		return luaL_error(L, "Enable argument must be a function.");
	}

	tcs34725Write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
	// Start a timer to wait TCS34725_EN_DELAY before calling tcs34725EnableDone
	os_timer_disarm (&tcs34725_timer);
	os_timer_setfn (&tcs34725_timer, (os_timer_func_t *)tcs34725EnableDone, NULL);
	os_timer_arm (&tcs34725_timer, TCS34725_EN_DELAY, 0); // trigger callback when readout is ready

	return 0;
}