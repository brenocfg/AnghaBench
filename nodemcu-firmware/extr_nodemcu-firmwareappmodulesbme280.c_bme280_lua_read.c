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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BME280_REGISTER_PRESS ; 
 int bme280_compensate_H (int) ; 
 int bme280_compensate_P (int) ; 
 int bme280_compensate_T (int) ; 
 int /*<<< orphan*/  bme280_isbme ; 
 double bme280_qfe2qnh (int,int) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8u_n (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int bme280_lua_read(lua_State* L) {
	uint8_t buf[8];
	uint32_t qfe;
	uint8_t calc_qnh = lua_isnumber(L, 1);

	r8u_n(BME280_REGISTER_PRESS, 8, buf);	// registers are P[3], T[3], H[2]

	// Must do Temp first since bme280_t_fine is used by the other compensation functions
	uint32_t adc_T = (uint32_t)(((buf[3] << 16) | (buf[4] << 8) | buf[5]) >> 4);
	if (adc_T == 0x80000 || adc_T == 0xfffff)
		return 0;
	lua_pushinteger(L, bme280_compensate_T(adc_T));

	uint32_t adc_P = (uint32_t)(((buf[0] << 16) | (buf[1] << 8) | buf[2]) >> 4);
	if (adc_P ==0x80000 || adc_P == 0xfffff) {
		lua_pushnil(L);
		calc_qnh = 0;
	} else {
		qfe = bme280_compensate_P(adc_P);
		lua_pushinteger(L, qfe);
	}

	uint32_t adc_H = (uint32_t)((buf[6] << 8) | buf[7]);
	if (!bme280_isbme || adc_H == 0x8000 || adc_H == 0xffff)
		lua_pushnil(L);
	else
		lua_pushinteger(L, bme280_compensate_H(adc_H));

	if (calc_qnh) { // have altitude
		int32_t h = luaL_checkinteger(L, 1);
		double qnh = bme280_qfe2qnh(qfe, h);
		lua_pushinteger(L, (int32_t)(qnh + 0.5));
		return 4;
	}
	return 3;
}