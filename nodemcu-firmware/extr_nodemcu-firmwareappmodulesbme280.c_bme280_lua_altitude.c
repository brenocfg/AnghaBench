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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,scalar_t__) ; 
 double pow (double,double) ; 

__attribute__((used)) static int bme280_lua_altitude(lua_State* L) {
	if (!lua_isnumber(L, 2)) {
		return luaL_error(L, "wrong arg range");
	}
	int32_t P = luaL_checkinteger(L, 1);
	int32_t qnh = luaL_checkinteger(L, 2);
	double h = (1.0 - pow((double)P/(double)qnh, 1.0/5.25588)) / 2.25577e-5 * 100.0;

	lua_pushinteger(L, (int32_t)(h + (((h<0)?-1:(h>0)) * 0.5)));
	return 1;
}