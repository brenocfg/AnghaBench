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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tcs34725IntegrationTime_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcs34725SetIntegrationTime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint8_t tcs34725LuaSetIntegrationTime(lua_State* L)
{
	tcs34725IntegrationTime_t it = luaL_checkinteger(L, 1);
	return tcs34725SetIntegrationTime(it,L);
}