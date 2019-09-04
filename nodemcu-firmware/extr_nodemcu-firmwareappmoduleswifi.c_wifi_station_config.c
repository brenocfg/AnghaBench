#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_2__ {int rssi; int /*<<< orphan*/  authmode; } ;
struct station_config {int bssid_set; int /*<<< orphan*/  bssid; int /*<<< orphan*/  password; int /*<<< orphan*/  ssid; TYPE_1__ threshold; } ;
typedef  int /*<<< orphan*/  sta_conf ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_OPEN ; 
 int /*<<< orphan*/  ets_str2macaddr (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  memset (struct station_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wifi_station_connect () ; 
 int /*<<< orphan*/  wifi_station_disconnect () ; 
 int /*<<< orphan*/  wifi_station_set_auto_connect (int /*<<< orphan*/ ) ; 
 int wifi_station_set_config (struct station_config*) ; 
 int wifi_station_set_config_current (struct station_config*) ; 

__attribute__((used)) static int wifi_station_config( lua_State* L )
{
  struct station_config sta_conf;
  bool auto_connect=true;
  bool save_to_flash=true;
  size_t sl, pl, ml;

  memset(&sta_conf, 0, sizeof(sta_conf));
  sta_conf.threshold.rssi = -127;
  sta_conf.threshold.authmode = AUTH_OPEN;

  if(lua_istable(L, 1))
  {
    lua_getfield(L, 1, "ssid");
    if (!lua_isnil(L, -1))
    {
      if( lua_isstring(L, -1) )
      {
        const char *ssid = luaL_checklstring( L, -1, &sl );
        luaL_argcheck(L, ((sl>=0 && sl<=sizeof(sta_conf.ssid)) ), 1, "ssid: length:0-32"); /* Zero-length SSID is valid as a way to clear config */
        memcpy(sta_conf.ssid, ssid, sl);
      }
      else
      {
        return luaL_argerror( L, 1, "ssid:not string" );
      }
    }
    else
    {
      return luaL_argerror( L, 1, "ssid required" );
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "pwd");
    if (!lua_isnil(L, -1))
    {
      if( lua_isstring(L, -1) )
      {
        const char *pwd = luaL_checklstring( L, -1, &pl );
        luaL_argcheck(L, ((pl>=0 && pl<=sizeof(sta_conf.password)) ), 1, "pwd: length:0-64"); /* WPA = min 8, WEP = min 5 ASCII characters for a 40-bit key */
        memcpy(sta_conf.password, pwd, pl);
      }
      else
      {
        return luaL_argerror( L, 1, "pwd:not string" );
      }
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "bssid");
    if (!lua_isnil(L, -1))
    {
      if (lua_isstring(L, -1))
      {
        const char *macaddr = luaL_checklstring( L, -1, &ml );
        luaL_argcheck(L, ((ml==sizeof("AA:BB:CC:DD:EE:FF")-1) ), 1, "bssid: FF:FF:FF:FF:FF:FF");
        ets_str2macaddr(sta_conf.bssid, macaddr);
        sta_conf.bssid_set = 1;
      }
      else
      {
        return luaL_argerror(L, 1, "bssid:not string");
      }
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "auto");
    if (!lua_isnil(L, -1))
    {
      if (lua_isboolean(L, -1))
      {
        auto_connect=lua_toboolean(L, -1);
      }
      else
      {
        return luaL_argerror(L, 1, "auto:not boolean");
      }
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "save");
    if (!lua_isnil(L, -1))
    {
      if (lua_isboolean(L, -1))
      {
        save_to_flash=lua_toboolean(L, -1);
      }
      else
      {
        return luaL_argerror(L, 1, "save:not boolean");
      }
    }
    else
    {
      save_to_flash=true;
    }
    lua_pop(L, 1);

#ifdef WIFI_SDK_EVENT_MONITOR_ENABLE

    lua_State* L_temp = NULL;

    lua_getfield(L, 1, "connect_cb");
    if (!lua_isnil(L, -1))
    {
      if (lua_isfunction(L, -1))
      {
          L_temp = lua_newthread(L);
          lua_pushnumber(L, EVENT_STAMODE_CONNECTED);
          lua_pushvalue(L, -3);
          lua_xmove(L, L_temp, 2);
          wifi_event_monitor_register(L_temp);
      }
      else
      {
        return luaL_argerror(L, 1, "connect_cb:not function");
      }
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "disconnect_cb");
    if (!lua_isnil(L, -1))
    {
      if (lua_isfunction(L, -1))
      {
          L_temp = lua_newthread(L);
          lua_pushnumber(L, EVENT_STAMODE_DISCONNECTED);
          lua_pushvalue(L, -3);
          lua_xmove(L, L_temp, 2);
          wifi_event_monitor_register(L_temp);
      }
      else
      {
        return luaL_argerror(L, 1, "disconnect_cb:not function");
      }
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "authmode_change_cb");
    if (!lua_isnil(L, -1))
    {
      if (lua_isfunction(L, -1))
      {
          L_temp = lua_newthread(L);
          lua_pushnumber(L, EVENT_STAMODE_AUTHMODE_CHANGE);
          lua_pushvalue(L, -3);
          lua_xmove(L, L_temp, 2);
          wifi_event_monitor_register(L_temp);
      }
      else
      {
        return luaL_argerror(L, 1, "authmode_change_cb:not function");
      }
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "got_ip_cb");
    if (!lua_isnil(L, -1))
    {
      if (lua_isfunction(L, -1))
      {
          L_temp = lua_newthread(L);
          lua_pushnumber(L, EVENT_STAMODE_GOT_IP);
          lua_pushvalue(L, -3);
          lua_xmove(L, L_temp, 2);
          wifi_event_monitor_register(L_temp);
      }
      else
      {
        return luaL_argerror(L, 1, "gotip_cb:not function");
      }
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "dhcp_timeout_cb");
    if (!lua_isnil(L, -1))
    {
      if (lua_isfunction(L, -1))
      {
          L_temp = lua_newthread(L);
          lua_pushnumber(L, EVENT_STAMODE_DHCP_TIMEOUT);
          lua_pushvalue(L, -3);
          lua_xmove(L, L_temp, 2);
          wifi_event_monitor_register(L_temp);
      }
      else
      {
        return luaL_argerror(L, 1, "dhcp_timeout_cb:not function");
      }
    }
    lua_pop(L, 1);

#endif

  }
  else
  {
    return luaL_argerror(L, 1, "config table not found!");
  }

#if defined(WIFI_DEBUG)
  char debug_temp[sizeof(sta_conf.password)+1];  //max password length + '\0'

  memset(debug_temp, 0, sizeof(debug_temp));
  memcpy(debug_temp, sta_conf.ssid, sizeof(sta_conf.ssid));
  WIFI_DBG("\n\tsta_conf.ssid=\"%s\" len=%d\n", debug_temp, sl);

  memset(debug_temp, 0, sizeof(debug_temp));
  memcpy(debug_temp, sta_conf.password, sizeof(sta_conf.password));
  WIFI_DBG("\tsta_conf.password=\"%s\" len=%d\n", debug_temp, pl);
  WIFI_DBG("\tsta_conf.bssid=\""MACSTR"\"\tbssid_set=%d\n", MAC2STR(sta_conf.bssid), sta_conf.bssid_set);
  WIFI_DBG("\tsave_to_flash=%s\n", save_to_flash ? "true":"false");
#endif

  wifi_station_disconnect();

  bool config_success;
  if(save_to_flash)
  {
    config_success = wifi_station_set_config(&sta_conf);
  }
  else
  {
    config_success = wifi_station_set_config_current(&sta_conf);
  }

  wifi_station_set_auto_connect((uint8)auto_connect);
  if(auto_connect)
  {
    wifi_station_connect();
  }

  lua_pushboolean(L, config_success);
  return 1;
}