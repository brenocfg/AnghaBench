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
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  system_deep_sleep (scalar_t__) ; 
 int /*<<< orphan*/  system_deep_sleep_instant (scalar_t__) ; 
 int /*<<< orphan*/  system_deep_sleep_set_option (int) ; 

__attribute__((used)) static int node_deepsleep( lua_State* L )
{
  uint64 us;
  uint8 option;
  //us = luaL_checkinteger( L, 1 );
  // Set deleep option, skip if nil
  if ( lua_isnumber(L, 2) )
  {
    option = lua_tointeger(L, 2);
    if ( option < 0 || option > 4)
      return luaL_error( L, "wrong arg range" );
    else
      system_deep_sleep_set_option( option );
  }
  bool instant = false;
  if (lua_isnumber(L, 3))
    instant = lua_tointeger(L, 3);
  // Set deleep time, skip if nil
  if ( lua_isnumber(L, 1) )
  {
    us = luaL_checknumber(L, 1);
    // if ( us <= 0 )
    if ( us < 0 )
      return luaL_error( L, "wrong arg range" );
    else
    {
      if (instant)
        system_deep_sleep_instant(us);
      else
        system_deep_sleep( us );
    }
  }
  return 0;
}