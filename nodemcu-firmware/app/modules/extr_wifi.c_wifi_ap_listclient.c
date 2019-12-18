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
struct station_info {int /*<<< orphan*/  ip; int /*<<< orphan*/  bssid; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  IP2STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPSTR ; 
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ ) ; 
 char* MACSTR ; 
 struct station_info* STAILQ_NEXT (struct station_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ STATION_MODE ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_add_sprintf_field (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wifi_get_opmode () ; 
 int /*<<< orphan*/  wifi_softap_free_station_info () ; 
 struct station_info* wifi_softap_get_station_info () ; 

__attribute__((used)) static int wifi_ap_listclient( lua_State* L )
{
  if (wifi_get_opmode() == STATION_MODE)
  {
    return luaL_error( L, "Can't list clients in STATION mode" );
  }

  char temp[64];

  lua_newtable(L);

  struct station_info * station = wifi_softap_get_station_info();
  struct station_info * next_station;
  while (station != NULL)
  {
    sprintf(temp, MACSTR, MAC2STR(station->bssid));
    wifi_add_sprintf_field(L, temp, IPSTR, IP2STR(&station->ip));
    station = STAILQ_NEXT(station, next);
  }
  wifi_softap_free_station_info();

  return 1;
}