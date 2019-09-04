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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  timer_ref; int /*<<< orphan*/  timer; int /*<<< orphan*/  i2c_addr; } ;
typedef  TYPE_1__ ads_ctrl_ud_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADS1115_POINTER_CONVERSION ; 
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_common (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ads1115_lua_readoutdone(void * param) {
    ads_ctrl_ud_t * ads_ctrl = (ads_ctrl_ud_t *)param;
    uint16_t raw = read_reg(ads_ctrl->i2c_addr, ADS1115_POINTER_CONVERSION);
    lua_State *L = lua_getstate();
    os_timer_disarm(&ads_ctrl->timer);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ads_ctrl->timer_ref);
    luaL_unref(L, LUA_REGISTRYINDEX, ads_ctrl->timer_ref);
    ads_ctrl->timer_ref = LUA_NOREF;
    read_common(ads_ctrl, raw, L);
    lua_call(L, 4, 0);
}