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
 int /*<<< orphan*/  TCS34725_ID ; 
 int /*<<< orphan*/  dbg_printf (char*,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int tcs34725Read8 (int /*<<< orphan*/ ) ; 

uint8_t tcs34725Setup(lua_State* L)
{
	uint8_t id = 0;

	/* Make sure we have the right IC (0x44 = TCS34725 and TCS34721) */
	id = tcs34725Read8(TCS34725_ID);
	dbg_printf("id: %x\n",id);
	if (id != 0x44) {
		return luaL_error(L, "No TCS34725 found.");
	}

	lua_pushinteger(L, 1);
	return 1;
}