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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  bme280_timer ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_connected_readout_ref ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bme280_readoutdone (void *arg)
{
	NODE_DBG("timer out\n");
	lua_State *L = lua_getstate();
	lua_rawgeti (L, LUA_REGISTRYINDEX, lua_connected_readout_ref);
	lua_call (L, 0, 0);
	luaL_unref (L, LUA_REGISTRYINDEX, lua_connected_readout_ref);
	os_timer_disarm (&bme280_timer);
}