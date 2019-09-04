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
 int DS18B20_EEPROM_TH ; 
 int DS18B20_EEPROM_TL ; 
 int* ds18b20_device_conf ; 
 int ds18b20_device_res ; 
 int /*<<< orphan*/ * ds18b20_device_rom ; 
 int /*<<< orphan*/  ds18b20_set_device (int /*<<< orphan*/ *) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 char* strchr (char const*,char const) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ds18b20_lua_setting(lua_State *L) {
	// check rom table and resolution setting
	if (!lua_istable(L, 1) || !lua_isnumber(L, 2)) {
		return luaL_error(L, "wrong arg range");
	}

	ds18b20_device_res = luaL_checkinteger(L, 2);

	if (!((ds18b20_device_res == 9) || (ds18b20_device_res == 10) || (ds18b20_device_res == 11) || (ds18b20_device_res == 12))) {
		return luaL_error(L, "Invalid argument: resolution");
	}

	// no change to th and tl setting
	ds18b20_device_conf[0] = DS18B20_EEPROM_TH;
	ds18b20_device_conf[1] = DS18B20_EEPROM_TL;
	ds18b20_device_conf[2] = ((ds18b20_device_res - 9) << 5) + 0x1F;

	uint8_t table_len = lua_objlen(L, 1);

	const char *str[table_len];
	const char *sep = ":";

	uint8_t string_index = 0;

	lua_pushnil(L);
	while (lua_next(L, -3)) {
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
		ds18b20_set_device(ds18b20_device_rom);
	}

	// set conversion delay once to max if sensors with higher resolution still on the bus
	ds18b20_device_res = 12;

	return 0;
}