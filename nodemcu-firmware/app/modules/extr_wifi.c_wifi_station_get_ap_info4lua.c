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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  temp ;
struct station_config {char* ssid; char* password; int /*<<< orphan*/  bssid; scalar_t__ bssid_set; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 char* MAC2STR (int /*<<< orphan*/ ) ; 
 char* MACSTR ; 
 int /*<<< orphan*/  WIFI_DBG (char*,...) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int strlen (char*) ; 
 int wifi_station_get_ap_info (struct station_config*) ; 

__attribute__((used)) static int wifi_station_get_ap_info4lua( lua_State* L )
{
  struct station_config config[5];
  char temp[sizeof(config[0].password)+1]; //max password length + '\0'
  uint8 number_of_aps = wifi_station_get_ap_info(config);

#if defined(WIFI_DEBUG)
  char debug_temp[128];
#endif
  lua_newtable(L);
  lua_pushnumber(L, number_of_aps);
  lua_setfield(L, -2, "qty");
  WIFI_DBG("\n\t# of APs stored in flash:%d\n", number_of_aps);
  WIFI_DBG(" %-6s %-32s %-64s %-17s\n", "index:", "ssid:", "password:", "bssid:");

  for(int i=0;i<number_of_aps;i++)
  {
    lua_newtable(L);

    memset(temp, 0, sizeof(temp));
    memcpy(temp, config[i].ssid, sizeof(config[i].ssid));
    lua_pushstring(L, temp);
    lua_setfield(L, -2, "ssid");
#if defined(WIFI_DEBUG)
    sprintf(debug_temp, " %-6d %-32s ", i, temp);
#endif

    memset(temp, 0, sizeof(temp));
    if(strlen(config[i].password) > 0) /* WPA = min 8, WEP = min 5 ASCII characters for a 40-bit key */
    {
      memcpy(temp, config[i].password, sizeof(config[i].password));
      lua_pushstring(L, temp);
      lua_setfield(L, -2, "pwd");
    }
#if defined(WIFI_DEBUG)
    sprintf(debug_temp + strlen(debug_temp), "%-64s ", temp);
#endif

    memset(temp, 0, sizeof(temp));
    if (config[i].bssid_set)
    {
      sprintf(temp, MACSTR, MAC2STR(config[i].bssid));
      lua_pushstring(L, temp);
      lua_setfield(L, -2, "bssid");
    }

#if defined(WIFI_DEBUG)
    WIFI_DBG("%s%-17s \n", debug_temp, temp);
#endif
    lua_pushnumber(L, i+1); //Add one, so that AP index follows Lua Conventions
    lua_insert(L, -2);
    lua_settable(L, -3);
  }
  return 1;
}