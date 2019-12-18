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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi ; 
 int /*<<< orphan*/  spi_mast_transaction (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int spi_transaction( lua_State *L )
{
  int id = luaL_checkinteger( L, 1 );

  MOD_CHECK_ID( spi, id );

  int cmd_bitlen = luaL_checkinteger( L, 2 );
  u16 cmd_data   = ( u16 )luaL_checkinteger( L, 3 );
  luaL_argcheck( L, 2, cmd_bitlen >= 0 && cmd_bitlen <= 16, "out of range" );

  int addr_bitlen = luaL_checkinteger( L, 4 );
  u32 addr_data   = ( u32 )luaL_checkinteger( L, 5 );
  luaL_argcheck( L, 4, addr_bitlen >= 0 && addr_bitlen <= 32, "out of range" );

  int mosi_bitlen = luaL_checkinteger( L, 6 );
  luaL_argcheck( L, 6, mosi_bitlen >= 0 && mosi_bitlen <= 512, "out of range" );

  int dummy_bitlen = luaL_checkinteger( L, 7 );
  luaL_argcheck( L, 7, dummy_bitlen >= 0 && dummy_bitlen <= 256, "out of range" );

  int miso_bitlen = luaL_checkinteger( L, 8 );
  luaL_argcheck( L, 8, miso_bitlen >= -512 && miso_bitlen <= 512, "out of range" );

  spi_mast_transaction( id, cmd_bitlen, cmd_data, addr_bitlen, addr_data,
			mosi_bitlen, dummy_bitlen, miso_bitlen );

  return 0;
}