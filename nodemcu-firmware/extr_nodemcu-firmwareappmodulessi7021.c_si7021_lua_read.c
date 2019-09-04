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
typedef  double uint16_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  SI7021_CMD_MEASURE_RH_HOLD ; 
 int /*<<< orphan*/  SI7021_CMD_READ_PREV_TEMP ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  read_reg (int /*<<< orphan*/ ,int*,int) ; 
 int si7021_crc8 (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int si7021_lua_read(lua_State* L) {

	uint8_t buf_h[3];	// first two byte data, third byte crc
	read_reg(SI7021_CMD_MEASURE_RH_HOLD, buf_h, 3);
	if (buf_h[2] != si7021_crc8(0, buf_h, 2))	//crc check
		return luaL_error(L, "crc error");
	double hum = (uint16_t)((buf_h[0] << 8) | buf_h[1]);
	hum = ((hum * 125) / 65536 - 6);
	int humdec = (int)((hum - (int)hum) * 1000);

	uint8_t buf_t[2];	// two byte data, no crc on combined temp measurement
	read_reg(SI7021_CMD_READ_PREV_TEMP, buf_t, 2);
	double temp = (uint16_t)((buf_t[0] << 8) | buf_t[1]);
	temp = ((temp * 175.72) / 65536 - 46.85);
	int tempdec = (int)((temp - (int)temp) * 1000);

	lua_pushnumber(L, hum);
	lua_pushnumber(L, temp);
	lua_pushinteger(L, humdec);
	lua_pushinteger(L, tempdec);

	return 4;
}