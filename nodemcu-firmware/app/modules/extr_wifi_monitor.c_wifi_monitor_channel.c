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
 scalar_t__ LUA_TNUMBER ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wifi_get_channel () ; 
 int /*<<< orphan*/  wifi_set_channel (int) ; 

__attribute__((used)) static int wifi_monitor_channel(lua_State *L) {
  lua_pushinteger(L, wifi_get_channel());
  if (lua_type(L, 1) == LUA_TNUMBER) {
    int channel = luaL_checkinteger(L, 1);

    if (channel < 1 || channel > 15) {
      return luaL_error(L, "Channel number (%d) is out of range", channel);
    }
    wifi_set_channel(channel);
  }

  return 1;
}