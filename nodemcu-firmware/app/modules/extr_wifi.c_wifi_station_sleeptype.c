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
 unsigned int LIGHT_SLEEP_T ; 
 unsigned int MODEM_SLEEP_T ; 
 unsigned int NONE_SLEEP_T ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 unsigned int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 unsigned int wifi_get_sleep_type () ; 
 int /*<<< orphan*/  wifi_set_sleep_type (unsigned int) ; 

__attribute__((used)) static int wifi_station_sleeptype( lua_State* L )
{
  unsigned type;

  if ( lua_isnumber(L, 1) )
  {
    type = lua_tointeger(L, 1);
    luaL_argcheck(L, (type == NONE_SLEEP_T || type == LIGHT_SLEEP_T || type == MODEM_SLEEP_T), 1, "range:0-2");
    if(!wifi_set_sleep_type(type)){
      lua_pushnil(L);
      return 1;
    }
  }

  type = wifi_get_sleep_type();
  lua_pushinteger( L, type );
  return 1;
}