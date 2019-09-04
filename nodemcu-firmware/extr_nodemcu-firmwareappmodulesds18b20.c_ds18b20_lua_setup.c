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
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds18b20_bus_pin ; 
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  onewire_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ow ; 
 int /*<<< orphan*/  platform_print_deprecation_note (char*,char*) ; 

__attribute__((used)) static int ds18b20_lua_setup(lua_State *L) {

	platform_print_deprecation_note("ds18b20 C module superseded by Lua implementation", "soon");

	// check ow bus pin value
	if (!lua_isnumber(L, 1) || lua_isnumber(L, 1) == 0) {
		return luaL_error(L, "wrong 1-wire pin");
	}

	ds18b20_bus_pin = luaL_checkinteger(L, 1);
	MOD_CHECK_ID(ow, ds18b20_bus_pin);
	onewire_init(ds18b20_bus_pin);
}