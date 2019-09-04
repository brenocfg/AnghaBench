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
typedef  int sint8 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int wifi_station_get_rssi () ; 

__attribute__((used)) static int wifi_station_getrssi( lua_State* L ){
  sint8 rssival=wifi_station_get_rssi();
  NODE_DBG("\n\tRSSI is %d\n", rssival);
  if (rssival<10)
  {
    lua_pushinteger(L, rssival);
  }
  else
  {
    lua_pushnil(L);
  }
  return 1;
}