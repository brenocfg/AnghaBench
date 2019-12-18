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
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 scalar_t__ LUA_TLIGHTFUNCTION ; 
 scalar_t__ LUA_TNUMBER ; 
 scalar_t__ STATION_IDLE ; 
 int /*<<< orphan*/  eventmon_call_on_disconnected (int /*<<< orphan*/  (*) ()) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int mon_mask ; 
 int mon_offset ; 
 int mon_value ; 
 int /*<<< orphan*/  recv_cb ; 
 int /*<<< orphan*/  start_actually_monitoring () ; 
 int /*<<< orphan*/  wifi_promiscuous_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_rx_cb ; 
 int /*<<< orphan*/  wifi_set_opmode_current (int) ; 
 int /*<<< orphan*/  wifi_set_promiscuous_rx_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_station_disconnect () ; 
 scalar_t__ wifi_station_get_connect_status () ; 
 int /*<<< orphan*/  wifi_station_set_auto_connect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wifi_monitor_start(lua_State *L) {
  int argno = 1;
  if (lua_type(L, argno) == LUA_TNUMBER) {
    int offset = luaL_checkinteger(L, argno);
    argno++;
    if (lua_type(L, argno) == LUA_TNUMBER) {
      int value = luaL_checkinteger(L, argno);

      int mask = 0xff;
      argno++;

      if (lua_type(L, argno) == LUA_TNUMBER) {
        mask = luaL_checkinteger(L, argno);
        argno++;
      }
      mon_offset = offset - 1;
      mon_value = value;
      mon_mask = mask;
    } else {
      return luaL_error(L, "Must supply offset and value");
    }
  } else {
    // Management frames by default
    mon_offset = 12;
    mon_value = 0x00;
    mon_mask = 0x0C;
  }
  if (lua_type(L, argno) == LUA_TFUNCTION || lua_type(L, argno) == LUA_TLIGHTFUNCTION)
  {
    lua_pushvalue(L, argno);  // copy argument (func) to the top of stack
    recv_cb = luaL_ref(L, LUA_REGISTRYINDEX);
    uint8 connect_status = wifi_station_get_connect_status();
    wifi_station_set_auto_connect(0);
    wifi_set_opmode_current(1);
    wifi_promiscuous_enable(0);
    wifi_station_disconnect();
    wifi_set_promiscuous_rx_cb(wifi_rx_cb);
    // Now we have to wait until we get the EVENT_STAMODE_DISCONNECTED event
    // before we can go further.
    if (connect_status == STATION_IDLE) {
      start_actually_monitoring();
    } else {
      eventmon_call_on_disconnected(start_actually_monitoring);
    }
    return 0;
  }
  return luaL_error(L, "Missing callback");
}