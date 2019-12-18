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
typedef  int /*<<< orphan*/  temp ;
struct station_config {scalar_t__ ssid; scalar_t__ password; int /*<<< orphan*/  bssid; int /*<<< orphan*/  bssid_set; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ ) ; 
 char* MACSTR ; 
 scalar_t__ lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (scalar_t__) ; 
 int /*<<< orphan*/  wifi_station_get_config (struct station_config*) ; 
 int /*<<< orphan*/  wifi_station_get_config_default (struct station_config*) ; 

__attribute__((used)) static int wifi_station_getconfig( lua_State* L, bool get_flash_cfg)
{
  struct station_config sta_conf;
  char temp[sizeof(sta_conf.password)+1]; //max password length + '\0'

  if(get_flash_cfg)
  {
    wifi_station_get_config_default(&sta_conf);
  }
  else
  {
    wifi_station_get_config(&sta_conf);
  }

  if(sta_conf.ssid==0)
  {
    lua_pushnil(L);
      return 1;
  }
  else
  {
    if(lua_isboolean(L, 1) && lua_toboolean(L, 1)==true)
    {
      lua_newtable(L);
      memset(temp, 0, sizeof(temp));
      memcpy(temp, sta_conf.ssid, sizeof(sta_conf.ssid));
      lua_pushstring(L, temp);
      lua_setfield(L, -2, "ssid");

      if(strlen(sta_conf.password) > 0) /* WPA = min 8, WEP = min 5 ASCII characters for a 40-bit key */
      {
        memset(temp, 0, sizeof(temp));
        memcpy(temp, sta_conf.password, sizeof(sta_conf.password));
        lua_pushstring(L, temp);
        lua_setfield(L, -2, "pwd");
      }

      lua_pushboolean(L, sta_conf.bssid_set);
      lua_setfield(L, -2, "bssid_set");

      memset(temp, 0, sizeof(temp));
      sprintf(temp, MACSTR, MAC2STR(sta_conf.bssid));
      lua_pushstring( L, temp);
      lua_setfield(L, -2, "bssid");

      return 1;
    }
    else
    {
      memset(temp, 0, sizeof(temp));
      memcpy(temp, sta_conf.ssid, sizeof(sta_conf.ssid));
      lua_pushstring(L, temp);
      memset(temp, 0, sizeof(temp));
      memcpy(temp, sta_conf.password, sizeof(sta_conf.password));
      lua_pushstring(L, temp);
      lua_pushinteger( L, sta_conf.bssid_set);
      sprintf(temp, MACSTR, MAC2STR(sta_conf.bssid));
      lua_pushstring( L, temp);
      return 4;
    }
  }
}