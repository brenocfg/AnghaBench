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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 double bme280_qfe2qnh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bme280_lua_qfe2qnh(lua_State* L) {
	if (!lua_isnumber(L, 2)) {
		return luaL_error(L, "wrong arg range");
	}
	int32_t qfe = luaL_checkinteger(L, 1);
	int32_t h = luaL_checkinteger(L, 2);
	double qnh = bme280_qfe2qnh(qfe, h);
	lua_pushinteger(L, (int32_t)(qnh + 0.5));
	return 1;
}