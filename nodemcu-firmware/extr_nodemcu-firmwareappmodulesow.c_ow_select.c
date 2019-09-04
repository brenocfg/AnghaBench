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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 size_t lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  onewire_select (unsigned int,char*) ; 
 int /*<<< orphan*/  ow ; 

__attribute__((used)) static int ow_select( lua_State *L )
{
  uint8_t rom[8];
  size_t datalen;
  int numdata, i;
  unsigned id = luaL_checkinteger( L, 1 );
  const char *pdata;
  MOD_CHECK_ID( ow, id );

  if( lua_istable( L, 2 ) )
  {
    datalen = lua_objlen( L, 2 );
    if (datalen!=8)
      return luaL_error( L, "wrong arg range" );
    for( i = 0; i < datalen; i ++ )
    {
      lua_rawgeti( L, 2, i + 1 );
      numdata = ( int )luaL_checkinteger( L, -1 );
      lua_pop( L, 1 );
      if( numdata > 255 )
        return luaL_error( L, "wrong arg range" );
      rom[i] = (uint8_t)numdata;
    }
  }
  else
  {
    pdata = luaL_checklstring( L, 2, &datalen );
    if (datalen!=8)
      return luaL_error( L, "wrong arg range" );
    for( i = 0; i < datalen; i ++ ){
      rom[i] = pdata[i];
    }
  }

  onewire_select(id, rom);
  return 0;
}