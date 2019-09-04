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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  ds18b20_bus_pin ; 
 int ds18b20_device_index ; 
 int ds18b20_device_res ; 
 int /*<<< orphan*/ * ds18b20_device_rom ; 
 scalar_t__ ds18b20_device_search ; 
 int /*<<< orphan*/  ds18b20_read_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds18b20_table_ref ; 
 int /*<<< orphan*/  ds18b20_timer ; 
 int /*<<< orphan*/  ds18b20_timer_ref ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ onewire_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char const) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ds18b20_lua_readoutdone(void) {

	lua_State *L = lua_getstate();
	os_timer_disarm(&ds18b20_timer);

	ds18b20_device_index = 1;
	// set conversion delay to min and change it after finding the sensor with the highest resolution setting
	ds18b20_device_res = 9;

	if (ds18b20_device_search) {
		// iterate through all sensors on the bus and read temperature, resolution and parasitc settings
		while (onewire_search(ds18b20_bus_pin, ds18b20_device_rom)) {
			ds18b20_read_device(ds18b20_device_rom);
		}
	} else {
		lua_rawgeti(L, LUA_REGISTRYINDEX, ds18b20_table_ref);
		uint8_t table_len = lua_objlen(L, -1);

		const char *str[table_len];
		const char *sep = ":";

		uint8_t string_index = 0;

		lua_pushnil(L);
		while (lua_next(L, -2)) {
			str[string_index] = lua_tostring(L, -1);
			lua_pop(L, 1);
			string_index++;
		}
		lua_pop(L, 1);

		for (uint8_t i = 0; i < string_index; i++) {
			for (uint8_t j = 0; j < 8; j++) {
				ds18b20_device_rom[j] = strtoul(str[i], NULL, 16);
				str[i] = strchr(str[i], *sep);
				if (str[i] == NULL || *str[i] == '\0') break;
				str[i]++;
			}
			ds18b20_read_device(ds18b20_device_rom);
		}
	}

	luaL_unref(L, LUA_REGISTRYINDEX, ds18b20_table_ref);
	ds18b20_table_ref = LUA_NOREF;

	luaL_unref(L, LUA_REGISTRYINDEX, ds18b20_timer_ref);
	ds18b20_timer_ref = LUA_NOREF;
}