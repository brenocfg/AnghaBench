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
 int BME280_FORCED_MODE ; 
 int /*<<< orphan*/  BME280_REGISTER_CONTROL ; 
 int /*<<< orphan*/  BME280_REGISTER_CONTROL_HUM ; 
 scalar_t__ BME280_SAMPLING_DELAY ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int bme280_mode ; 
 int bme280_ossh ; 
 scalar_t__ bme280_readoutdone ; 
 int /*<<< orphan*/  bme280_timer ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_connected_readout_ref ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w8u (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bme280_lua_startreadout(lua_State* L) {
	uint32_t delay;

	if (lua_isnumber(L, 1)) {
		delay = luaL_checkinteger(L, 1);
		if (!delay) {delay = BME280_SAMPLING_DELAY;} // if delay is 0 then set the default delay
	}

	if (!lua_isnoneornil(L, 2)) {
		lua_pushvalue(L, 2);
		lua_connected_readout_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	} else {
		lua_connected_readout_ref = LUA_NOREF;
	}

	w8u(BME280_REGISTER_CONTROL_HUM, bme280_ossh);
	w8u(BME280_REGISTER_CONTROL, (bme280_mode & 0xFC) | BME280_FORCED_MODE);
	NODE_DBG("control old: %x, control: %x, delay: %d\n", bme280_mode, (bme280_mode & 0xFC) | BME280_FORCED_MODE, delay);

	if (lua_connected_readout_ref != LUA_NOREF) {
		NODE_DBG("timer armed\n");
		os_timer_disarm (&bme280_timer);
		os_timer_setfn (&bme280_timer, (os_timer_func_t *)bme280_readoutdone, L);
		os_timer_arm (&bme280_timer, delay, 0); // trigger callback when readout is ready
	}
	return 0;
}