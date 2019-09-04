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
 int /*<<< orphan*/  SI7021_CMD_ID1 ; 
 int /*<<< orphan*/  SI7021_CMD_ID2 ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_serial (int /*<<< orphan*/ ,int*,int) ; 
 int si7021_crc8 (int,int*,int) ; 

__attribute__((used)) static int si7021_lua_serial(lua_State* L) {

	uint32_t serial_a;
	uint8_t crc = 0;
	uint8_t buf_s_1[8];	// every second byte contains crc
	read_serial(SI7021_CMD_ID1, buf_s_1, 8);
	for(uint8_t i = 0; i <= 6; i+=2) {
		crc = si7021_crc8(crc, buf_s_1+i, 1);
		if (buf_s_1[i+1] != crc)
			return luaL_error(L, "crc error");
		serial_a = (serial_a << 8) + buf_s_1[i];
	}

	uint32_t serial_b;
	crc = 0;
	uint8_t buf_s_2[6]; // every third byte contains crc
	read_serial(SI7021_CMD_ID2, buf_s_2, 6);
	for(uint8_t i = 0; i <=3; i+=3) {
		crc = si7021_crc8(crc, buf_s_2+i, 2);
		if (buf_s_2[i+2] != crc)
			return luaL_error(L, "crc error");
		serial_b = (serial_b << 16) + (buf_s_2[i] << 8) + buf_s_2[i+1];
	}

	lua_pushinteger(L, serial_a);
	lua_pushinteger(L, serial_b);

	return 2;
}