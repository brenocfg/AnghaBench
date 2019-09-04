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

/* Variables and functions */
 int /*<<< orphan*/  BME280_REGISTER_TEMP ; 
 int bme280_compensate_H (int) ; 
 int bme280_compensate_T (int) ; 
 int /*<<< orphan*/  bme280_isbme ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r8u_n (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int bme280_lua_humi(lua_State* L) {
	if (!bme280_isbme) return 0;
	uint8_t buf[5];
	r8u_n(BME280_REGISTER_TEMP, 5, buf); // registers are P[3], T[3], H[2]

	uint32_t adc_T = (uint32_t)(((buf[0] << 16) | (buf[1] << 8) | buf[2]) >> 4);
	uint32_t T = bme280_compensate_T(adc_T);
	uint32_t adc_H = (uint32_t)((buf[3] << 8) | buf[4]);
	if (adc_T == 0x80000 || adc_T == 0xfffff || adc_H == 0x8000 || adc_H == 0xffff)
		return 0;
	lua_pushinteger(L, bme280_compensate_H(adc_H));
	lua_pushinteger(L, T);
	return 2;
}