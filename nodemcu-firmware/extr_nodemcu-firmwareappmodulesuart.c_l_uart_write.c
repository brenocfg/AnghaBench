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
typedef  char const u8 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_TNUMBER ; 
 int /*<<< orphan*/  LUA_TSTRING ; 
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,int) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 size_t lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_uart_send (int,char const) ; 
 int /*<<< orphan*/  uart ; 

__attribute__((used)) static int l_uart_write( lua_State* L )
{
  int id;
  const char* buf;
  size_t len, i;
  int total = lua_gettop( L ), s;

  id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( uart, id );
  for( s = 2; s <= total; s ++ )
  {
    if( lua_type( L, s ) == LUA_TNUMBER )
    {
      len = lua_tointeger( L, s );
      if( len > 255 )
        return luaL_error( L, "invalid number" );
      platform_uart_send( id, ( u8 )len );
    }
    else
    {
      luaL_checktype( L, s, LUA_TSTRING );
      buf = lua_tolstring( L, s, &len );
      for( i = 0; i < len; i ++ )
        platform_uart_send( id, buf[ i ] );
    }
  }
  return 0;
}