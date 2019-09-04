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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  bmp085_pressure_raw (int) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmp085_lua_pressure_raw(lua_State* L) {
    uint8_t oss = 0;
    int32_t p;

    if (lua_isnumber(L, 1)) {
        oss = luaL_checkinteger(L, 1);
        if (oss > 3)  {
            oss = 3;
        }
    }

    p = bmp085_pressure_raw(oss);
    lua_pushinteger(L, p);
    return 1;
}