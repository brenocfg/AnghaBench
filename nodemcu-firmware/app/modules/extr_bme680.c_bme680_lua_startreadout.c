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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  os_timer_func_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  BME680_CONF_OS_H_ADDR ; 
 int /*<<< orphan*/  BME680_CONF_T_P_MODE_ADDR ; 
 int BME680_FORCED_MODE ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 scalar_t__ bme280_readoutdone ; 
 int bme680_mode ; 
 int /*<<< orphan*/  bme680_timer ; 
 scalar_t__ calc_dur () ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_connected_readout_ref ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int os_hum ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w8u (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bme680_lua_startreadout(lua_State* L) {
	uint32_t delay;

	if (lua_isnumber(L, 1)) {
		delay = luaL_checkinteger(L, 1);
		if (!delay) {delay = calc_dur();} // if delay is 0 then set the default delay
	}

	if (!lua_isnoneornil(L, 2)) {
		lua_pushvalue(L, 2);
		lua_connected_readout_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	} else {
		lua_connected_readout_ref = LUA_NOREF;
	}

  w8u(BME680_CONF_OS_H_ADDR, os_hum);
  w8u(BME680_CONF_T_P_MODE_ADDR, (bme680_mode & 0xFC) | BME680_FORCED_MODE);

	NODE_DBG("control old: %x, control: %x, delay: %d\n", bme680_mode, (bme680_mode & 0xFC) | BME680_FORCED_MODE, delay);

	if (lua_connected_readout_ref != LUA_NOREF) {
		NODE_DBG("timer armed\n");
		os_timer_disarm (&bme680_timer);
		os_timer_setfn (&bme680_timer, (os_timer_func_t *)bme280_readoutdone, L);
		os_timer_arm (&bme680_timer, delay, 0); // trigger callback when readout is ready
	}
	return 0;
}