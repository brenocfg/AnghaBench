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
 int /*<<< orphan*/  wifi_station_connect () ; 

__attribute__((used)) static int wifi_station_connect4lua( lua_State* L )
{
#ifdef WIFI_SDK_EVENT_MONITOR_ENABLE
  if(lua_isfunction(L, 1)){
    lua_pushnumber(L, EVENT_STAMODE_CONNECTED);
    lua_pushvalue(L, 1);
    lua_remove(L, 1);
    wifi_event_monitor_register(L);
  }
#endif
  wifi_station_connect();
  return 0;
}