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
typedef  void* uint8_t ;
typedef  int uint16_t ;
struct softap_config {size_t ssid_len; int channel; int max_connection; int beacon_interval; void* ssid_hidden; void* authmode; int /*<<< orphan*/  password; int /*<<< orphan*/  ssid; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lua_Number ;
typedef  int lua_Integer ;

/* Variables and functions */
 int AUTH_MAX ; 
 void* AUTH_OPEN ; 
 void* AUTH_WPA_WPA2_PSK ; 
 int LUA_TBOOLEAN ; 
 int LUA_TNONE ; 
 int LUA_TNUMBER ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_typerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wifi_softap_set_config (struct softap_config*) ; 
 int wifi_softap_set_config_current (struct softap_config*) ; 

__attribute__((used)) static int wifi_ap_config( lua_State* L )
{
  if (!lua_istable(L, 1))
  {
    return luaL_typerror(L, 1, lua_typename(L, LUA_TTABLE));
  }

  struct softap_config config;
  bool save_to_flash=true;
  size_t sl = 0 , pl = 0;
  lua_Integer lint=0;
  int Ltype_tmp=LUA_TNONE;

  memset(config.ssid, 0, sizeof(config.ssid));
  memset(config.password, 0, sizeof(config.password));

  lua_getfield(L, 1, "ssid");
  if (!lua_isnil(L, -1)) /* found? */
  {
    if( lua_isstring(L, -1) )   // deal with the ssid string
    {
      const char *ssid = luaL_checklstring( L, -1, &sl );
      luaL_argcheck(L, ((sl>=1 && sl<=sizeof(config.ssid)) ), 1, "ssid: length:1-32");
      memcpy(config.ssid, ssid, sl);
      config.ssid_len = sl;
      config.ssid_hidden = 0;
    }
    else
    {
      return luaL_argerror( L, 1, "ssid: not string" );
    }
  }
  else
  {
    return luaL_argerror( L, 1, "ssid: required" );
  }
  lua_pop(L, 1);


  lua_getfield(L, 1, "pwd");
  if (!lua_isnil(L, -1)) /* found? */
  {
    if( lua_isstring(L, -1) )   // deal with the password string
    {
      const char *pwd = luaL_checklstring( L, -1, &pl );
      luaL_argcheck(L, (pl>=8 && pl<=sizeof(config.password)), 1, "pwd: length:0 or 8-64");
      memcpy(config.password, pwd, pl);
      config.authmode = AUTH_WPA_WPA2_PSK;
    }
    else
    {
      return luaL_argerror( L, 1, "pwd: not string" );
    }
  }
  else
  {
    config.authmode = AUTH_OPEN;
  }
  lua_pop(L, 1);

  lua_getfield(L, 1, "auth");
  if (!lua_isnil(L, -1))
  {
    if(lua_isnumber(L, -1))
    {
      lint=luaL_checkinteger(L, -1);
      luaL_argcheck(L, (lint >= 0 && lint < AUTH_MAX), 1, "auth: Range:0-4");
      config.authmode = (uint8_t)luaL_checkinteger(L, -1);
    }
    else
    {
      return luaL_argerror(L, 1, "auth: not number");
    }

  }
  lua_pop(L, 1);


  lua_getfield(L, 1, "channel");
  if (!lua_isnil(L, -1))
  {
    if(lua_isnumber(L, -1))
    {
      lint=luaL_checkinteger(L, -1);
      luaL_argcheck(L, (lint >= 1 && lint <= 13), 1, "channel: Range:1-13");
      config.channel = (uint8_t)lint;
    }
    else
    {
      luaL_argerror(L, 1, "channel: not number");
    }
  }
  else
  {
    config.channel = 6;
  }
  lua_pop(L, 1);


  lua_getfield(L, 1, "hidden");
  if (!lua_isnil(L, -1))
  {
    Ltype_tmp=lua_type(L, -1);
    if(Ltype_tmp==LUA_TNUMBER||Ltype_tmp==LUA_TBOOLEAN)
    {
      if(Ltype_tmp==LUA_TNUMBER)
      {
        lint=luaL_checkinteger(L, -1);
      }

      if(Ltype_tmp==LUA_TBOOLEAN)
      {
        lint=(lua_Number)lua_toboolean(L, -1);
      }

      luaL_argcheck(L, (lint == 0 || lint==1), 1, "hidden: 0 or 1");
      config.ssid_hidden = (uint8_t)lint;
    }
    else
    {
      return luaL_argerror(L, 1, "hidden: not boolean");
    }
  }
  else
  {
    config.ssid_hidden = 0;
  }
  lua_pop(L, 1);


  lua_getfield(L, 1, "max");
  if (!lua_isnil(L, -1))
  {
    if(lua_isnumber(L, -1))
    {
      lint=luaL_checkinteger(L, -1);
      luaL_argcheck(L, (lint >= 1 && lint <= 4), 1, "max: 1-4");

      config.max_connection = (uint8_t)lint;
    }
    else
    {
      return luaL_argerror(L, 1, "max: not number");
    }
  }
  else
  {
    config.max_connection = 4;
  }
  lua_pop(L, 1);


  lua_getfield(L, 1, "beacon");
  if (!lua_isnil(L, -1))
  {
    if(lua_isnumber(L, -1))
    {
      lint=luaL_checkinteger(L, -1);
      luaL_argcheck(L, (lint >= 100 && lint <= 60000), 1, "beacon: 100-60000");
      config.beacon_interval = (uint16_t)lint;
    }
    else
    {
      return luaL_argerror(L, 1, "beacon: not number");
    }
  }
  else
  {
    config.beacon_interval = 100;
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
      return luaL_argerror(L, 1, "save: not boolean");
    }
  }
  lua_pop(L, 1);

#ifdef WIFI_SDK_EVENT_MONITOR_ENABLE

    lua_State* L_temp = NULL;

    lua_getfield(L, 1, "staconnected_cb");
    if (!lua_isnil(L, -1))
    {
      if (lua_isfunction(L, -1))
      {
          L_temp = lua_newthread(L);
          lua_pushnumber(L, EVENT_SOFTAPMODE_STACONNECTED);
          lua_pushvalue(L, -3);
          lua_xmove(L, L_temp, 2);
          wifi_event_monitor_register(L_temp);
      }
      else
      {
        return luaL_argerror(L, 1, "staconnected_cb:not function");
      }
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "stadisconnected_cb");
    if (!lua_isnil(L, -1))
    {
      if (lua_isfunction(L, -1))
      {
          L_temp = lua_newthread(L);
          lua_pushnumber(L, EVENT_SOFTAPMODE_STADISCONNECTED);
          lua_pushvalue(L, -3);
          lua_xmove(L, L_temp, 2);
          wifi_event_monitor_register(L_temp);
      }
      else
      {
        return luaL_argerror(L, 1, "stadisconnected_cb:not function");
      }
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "probereq_cb");
    if (!lua_isnil(L, -1))
    {
      if (lua_isfunction(L, -1))
      {
          L_temp = lua_newthread(L);
          lua_pushnumber(L, EVENT_SOFTAPMODE_PROBEREQRECVED);
          lua_pushvalue(L, -3);
          lua_xmove(L, L_temp, 2);
          wifi_event_monitor_register(L_temp);
      }
      else
      {
        return luaL_argerror(L, 1, "probereq_cb:not function");
      }
    }
    lua_pop(L, 1);

#endif

#if defined(WIFI_DEBUG)
  char debug_temp[sizeof(config.password)+1];
  memset(debug_temp, 0, sizeof(debug_temp));
  memcpy(debug_temp, config.ssid, sizeof(config.ssid));
  WIFI_DBG("\n\tconfig.ssid=\"%s\" len=%d\n", debug_temp, sl);
  memset(debug_temp, 0, sizeof(debug_temp));
  memcpy(debug_temp, config.password, sizeof(config.password));
  WIFI_DBG("\tconfig.password=\"%s\" len=%d\n", debug_temp, pl);
  WIFI_DBG("\tconfig.authmode=%d\n", config.authmode);
  WIFI_DBG("\tconfig.channel=%d\n", config.channel);
  WIFI_DBG("\tconfig.ssid_hidden=%d\n", config.ssid_hidden);
  WIFI_DBG("\tconfig.max_connection=%d\n", config.max_connection);
  WIFI_DBG("\tconfig.beacon_interval=%d\n", config.beacon_interval);
  WIFI_DBG("\tsave_to_flash=%s\n", save_to_flash ? "true":"false");
#endif

  bool config_success;
  if(save_to_flash)
  {
    config_success = wifi_softap_set_config(&config);
  }
  else
  {
    config_success = wifi_softap_set_config_current(&config);
  }

  lua_pushboolean(L, config_success);
  return 1;
}