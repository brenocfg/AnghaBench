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
 int /*<<< orphan*/  EVENT_STAMODE_DISCONNECTED ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wifi_event_monitor_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wifi_station_disconnect () ; 

__attribute__((used)) static int wifi_station_disconnect4lua( lua_State* L )
{
#ifdef WIFI_SDK_EVENT_MONITOR_ENABLE
  if(lua_isfunction(L, 1)){
    lua_pushnumber(L, EVENT_STAMODE_DISCONNECTED);
    lua_pushvalue(L, 1);
    lua_remove(L, 1);
    wifi_event_monitor_register(L);
  }
#endif
  wifi_station_disconnect();
  return 0;
}