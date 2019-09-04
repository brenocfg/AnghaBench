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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  TCS34725_BDATAL ; 
 int /*<<< orphan*/  TCS34725_CDATAL ; 
 int /*<<< orphan*/  TCS34725_GDATAL ; 
 int /*<<< orphan*/  TCS34725_RDATAL ; 
 int /*<<< orphan*/  _tcs34725Initialised ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcs34725Read16 (int /*<<< orphan*/ ) ; 

uint8_t tcs34725GetRawData(lua_State* L)
{
	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t c;

	if (!_tcs34725Initialised)
	{
		return luaL_error(L, "TCS34725 not initialised.");
	}

	c = tcs34725Read16(TCS34725_CDATAL);
	r = tcs34725Read16(TCS34725_RDATAL);
	g = tcs34725Read16(TCS34725_GDATAL);
	b = tcs34725Read16(TCS34725_BDATAL);
	lua_pushinteger(L, c);
	lua_pushinteger(L, r);
	lua_pushinteger(L, g);
	lua_pushinteger(L, b);
	return 4;
}