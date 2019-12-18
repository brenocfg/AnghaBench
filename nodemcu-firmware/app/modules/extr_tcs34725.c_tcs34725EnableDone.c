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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  TCS34725_ENABLE ; 
 int TCS34725_ENABLE_AEN ; 
 int TCS34725_ENABLE_PON ; 
 int /*<<< orphan*/  TCS34725_GAIN_60X ; 
 int /*<<< orphan*/  TCS34725_INTEGRATIONTIME_2_4MS ; 
 int _tcs34725Initialised ; 
 int /*<<< orphan*/  cb_tcs_en ; 
 int /*<<< orphan*/  dbg_printf (char*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcs34725SetGain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcs34725SetIntegrationTime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcs34725Write8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcs34725_timer ; 

uint8_t tcs34725EnableDone()
{
	dbg_printf("Enable finished\n");
	lua_State *L = lua_getstate();
	os_timer_disarm (&tcs34725_timer);
	tcs34725Write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);

	/* Ready to go ... set the initialised flag */
	_tcs34725Initialised = true;

	/* This needs to take place after the initialisation flag! */
	tcs34725SetIntegrationTime(TCS34725_INTEGRATIONTIME_2_4MS, L);
	tcs34725SetGain(TCS34725_GAIN_60X, L);

	lua_rawgeti(L, LUA_REGISTRYINDEX, cb_tcs_en); // Get the callback to call
	luaL_unref(L, LUA_REGISTRYINDEX, cb_tcs_en); // Unregister the callback to avoid leak
	cb_tcs_en = LUA_NOREF;
	lua_call(L, 0, 0);

	return 0;
}