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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv_cb ; 
 int /*<<< orphan*/  wifi_promiscuous_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_set_opmode_current (int) ; 

__attribute__((used)) static int wifi_monitor_stop(lua_State *L) {
  wifi_promiscuous_enable(0);
  wifi_set_opmode_current(1);
  luaL_unref(L, LUA_REGISTRYINDEX, recv_cb);
  recv_cb = LUA_NOREF;
  return 0;
}