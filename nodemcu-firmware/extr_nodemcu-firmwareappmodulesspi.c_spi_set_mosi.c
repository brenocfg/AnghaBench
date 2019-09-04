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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_TSTRING ; 
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi ; 
 int /*<<< orphan*/  spi_mast_blkset (int,size_t,char const*) ; 
 int /*<<< orphan*/  spi_mast_set_mosi (int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_set_mosi( lua_State *L )
{
  int id = luaL_checkinteger( L, 1 );

  MOD_CHECK_ID( spi, id );

  if (lua_type( L, 2 ) == LUA_TSTRING) {
    size_t len;
    const char *data = luaL_checklstring( L, 2, &len );
    luaL_argcheck( L, 2, len <= 64, "out of range" );

    spi_mast_blkset( id, len * 8, data );

  } else {
    int offset = luaL_checkinteger( L, 2 );
    int bitlen = luaL_checkinteger( L, 3 );

    luaL_argcheck( L, 2, offset >= 0 && offset <= 511, "out of range" );
    luaL_argcheck( L, 3, bitlen >= 1 && bitlen <= 32, "out of range" );

    for (int argn = 4; argn <= lua_gettop( L ); argn++, offset += bitlen ) {
      u32 data = ( u32 )luaL_checkinteger(L, argn );

      if (offset + bitlen > 512) {
        return luaL_error( L, "data range exceeded > 512 bits" );
      }

      spi_mast_set_mosi( id, offset, bitlen, data );
    }
  }

  return 0;
}