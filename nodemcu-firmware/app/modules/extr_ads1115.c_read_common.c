#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  gain; } ;
typedef  TYPE_1__ ads_ctrl_ud_t ;

/* Variables and functions */
 double get_mvolt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 

__attribute__((used)) static void read_common(ads_ctrl_ud_t * ads_ctrl, uint16_t raw, lua_State *L) {
    double mvolt = get_mvolt(ads_ctrl->gain, raw);
#ifdef LUA_NUMBER_INTEGRAL
    int sign;
    if (mvolt == 0) {
        sign = 0;
    } else if (mvolt > 0) {
        sign = 1;
    } else {
        sign = -1;
    }
    int uvolt;
    if (sign >= 0) {
        uvolt = (int)((mvolt - (int)mvolt) * 1000 + 0.5);
    } else {
        uvolt = -(int)((mvolt - (int)mvolt) * 1000 - 0.5);
        mvolt = -mvolt;
    }
    lua_pushnumber(L, mvolt);
    lua_pushinteger(L, uvolt);
    lua_pushinteger(L, raw);
    lua_pushinteger(L, sign);
#else
    lua_pushnumber(L, mvolt);
    lua_pushnil(L);
    lua_pushinteger(L, raw);
    lua_pushnil(L);
#endif
}