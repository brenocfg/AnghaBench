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
typedef  int /*<<< orphan*/  os_timer_func_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  DS18B20_FUNC_CONVERT ; 
 int /*<<< orphan*/  DS18B20_ROM_SKIP ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 scalar_t__ LUA_TLIGHTFUNCTION ; 
 int /*<<< orphan*/  SWTIMER_DROP ; 
 int /*<<< orphan*/  SWTIMER_REG_CB (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds18b20_bus_pin ; 
 int /*<<< orphan*/  ds18b20_device_family ; 
 int ds18b20_device_res ; 
 int ds18b20_device_search ; 
 scalar_t__ ds18b20_lua_readoutdone ; 
 int ds18b20_table_offset ; 
 void* ds18b20_table_ref ; 
 int /*<<< orphan*/  ds18b20_timer ; 
 void* ds18b20_timer_ref ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  onewire_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onewire_target_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onewire_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds18b20_lua_read(lua_State *L) {

	luaL_argcheck(L, (lua_type(L, 1) == LUA_TFUNCTION || lua_type(L, 1) == LUA_TLIGHTFUNCTION), 1, "Must be function");

	lua_pushvalue(L, 1);
	ds18b20_timer_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	if (!lua_istable(L, 2)) {
		return luaL_error(L, "wrong arg range");
	}

	if (lua_isnumber(L, 3)) {
		ds18b20_device_family = luaL_checkinteger(L, 3);
		onewire_target_search(ds18b20_bus_pin, ds18b20_device_family);
		ds18b20_table_offset = -3;
	} else {
		ds18b20_table_offset = -2;
	}

	lua_pushvalue(L, 2);
	ds18b20_table_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	lua_pushnil(L);
	if (lua_next(L, ds18b20_table_offset)) {
		lua_pop(L, 2);
		ds18b20_device_search = 0;
	} else {
		ds18b20_device_search = 1;
	}

	os_timer_disarm(&ds18b20_timer);

	// perform a temperature conversion for all sensors and set timer
	onewire_reset(ds18b20_bus_pin);
	onewire_write(ds18b20_bus_pin, DS18B20_ROM_SKIP, 0);
	onewire_write(ds18b20_bus_pin, DS18B20_FUNC_CONVERT, 1);
	os_timer_setfn(&ds18b20_timer, (os_timer_func_t *)ds18b20_lua_readoutdone, NULL);
	SWTIMER_REG_CB(ds18b20_lua_readoutdone, SWTIMER_DROP);
		//The function ds18b20_lua_readoutdone reads the temperature from the sensor(s) after a set amount of time depending on temperature resolution
	  //MY guess: If this timer manages to get suspended before it fires and the temperature data is time sensitive then resulting data would be invalid and should be discarded

	switch (ds18b20_device_res) {
		case (9):
			os_timer_arm(&ds18b20_timer, 95, 0);
			break;
		case (10):
			os_timer_arm(&ds18b20_timer, 190, 0);
			break;
		case (11):
			os_timer_arm(&ds18b20_timer, 380, 0);
			break;
		case (12):
			os_timer_arm(&ds18b20_timer, 760, 0);
			break;
	}
}