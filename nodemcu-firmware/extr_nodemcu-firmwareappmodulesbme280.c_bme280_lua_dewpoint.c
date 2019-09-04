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
 double const ln (double) ; 
 double luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bme280_lua_dewpoint(lua_State* L) {
	if (!lua_isnumber(L, 2)) {
		return luaL_error(L, "wrong arg range");
	}
	double H = luaL_checkinteger(L, 1)/100000.0;
	double T = luaL_checkinteger(L, 2)/100.0;

	const double c243 = 243.5;
	const double c17 = 17.67;
	double c = ln(H) + ((c17 * T) / (c243 + T));
	double d = (c243 * c)/(c17 - c) * 100.0;

	lua_pushinteger(L, (int32_t)(d + (((d<0)?-1:(d>0)) * 0.5)));
	return 1;
}