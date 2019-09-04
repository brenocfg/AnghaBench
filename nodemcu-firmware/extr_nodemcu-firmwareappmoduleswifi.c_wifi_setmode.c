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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TBOOLEAN ; 
 unsigned int NULL_MODE ; 
 unsigned int SOFTAP_MODE ; 
 unsigned int STATIONAP_MODE ; 
 unsigned int STATION_MODE ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_typerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,unsigned int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wifi_get_opmode () ; 
 int /*<<< orphan*/  wifi_set_opmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_set_opmode_current (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wifi_setmode( lua_State* L )
{
  unsigned mode;
  bool save_to_flash=true;
  mode = luaL_checkinteger( L, 1 );
  luaL_argcheck(L, mode == STATION_MODE || mode == SOFTAP_MODE || mode == STATIONAP_MODE || mode == NULL_MODE, 1, "Invalid mode");

  if(!lua_isnoneornil(L, 2))
  {
    if(!lua_isboolean(L, 2))
    {
      luaL_typerror(L, 2, lua_typename(L, LUA_TBOOLEAN));
    }
    save_to_flash=lua_toboolean(L, 2);
  }

  if(save_to_flash)
  {
    wifi_set_opmode( (uint8_t)mode);
  }
  else
  {
    wifi_set_opmode_current( (uint8_t)mode);
  }

  mode = (unsigned)wifi_get_opmode();
  lua_pushinteger( L, mode );
  return 1;
}