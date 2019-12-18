#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int samples_value; int threshold_low; int threshold_hi; int config; int /*<<< orphan*/  timer_ref; int /*<<< orphan*/  mode; int /*<<< orphan*/  comp; int /*<<< orphan*/  samples; int /*<<< orphan*/  gain; scalar_t__ i2c_addr; scalar_t__ chip_id; } ;
typedef  TYPE_1__ ads_ctrl_ud_t ;

/* Variables and functions */
 scalar_t__ ADS1115_ADS1115 ; 
 int /*<<< orphan*/  ADS1115_CQUE_NONE ; 
 int ADS1115_DEFAULT_CONFIG_REG ; 
 int /*<<< orphan*/  ADS1115_DR_128SPS ; 
 int /*<<< orphan*/  ADS1115_MODE_SINGLE ; 
 int /*<<< orphan*/  ADS1115_PGA_6_144V ; 
 int /*<<< orphan*/  ADS1115_POINTER_CONFIG ; 
 int IS_I2C_ADDR_VALID (scalar_t__) ; 
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  metatable_name ; 
 int read_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 char* unexpected_value ; 

__attribute__((used)) static int ads1115_lua_register(lua_State *L, uint8_t chip_id) {
    uint8_t i2c_id = luaL_checkinteger(L, 1);
    luaL_argcheck(L, 0 == i2c_id, 1, "i2c_id must be 0");
    uint8_t i2c_addr = luaL_checkinteger(L, 2);
    luaL_argcheck(L, IS_I2C_ADDR_VALID(i2c_addr), 2, unexpected_value);
    uint16_t config_read = read_reg(i2c_addr, ADS1115_POINTER_CONFIG);
    if (config_read == 0xFFFF) {
        return luaL_error(L, "found no device");
    }
    if (config_read != ADS1115_DEFAULT_CONFIG_REG) {
        return luaL_error(L, "unexpected config value (%p) please reset device before calling this function", config_read);
    }
    ads_ctrl_ud_t *ads_ctrl = (ads_ctrl_ud_t *)lua_newuserdata(L, sizeof(ads_ctrl_ud_t));
    if (NULL == ads_ctrl) {
        return luaL_error(L, "ads1115 malloc: out of memory");
    }
    luaL_getmetatable(L, metatable_name);
    lua_setmetatable(L, -2);
    ads_ctrl->chip_id = chip_id;
    ads_ctrl->i2c_addr = i2c_addr;
    ads_ctrl->gain = ADS1115_PGA_6_144V;
    ads_ctrl->samples = ADS1115_DR_128SPS;
    ads_ctrl->samples_value = chip_id == ADS1115_ADS1115 ? 128 : 1600;
    ads_ctrl->comp = ADS1115_CQUE_NONE;
    ads_ctrl->mode = ADS1115_MODE_SINGLE;
    ads_ctrl->threshold_low = 0x8000;
    ads_ctrl->threshold_hi = 0x7FFF;
    ads_ctrl->config = ADS1115_DEFAULT_CONFIG_REG;
    ads_ctrl->timer_ref = LUA_NOREF;
    return 1;
}