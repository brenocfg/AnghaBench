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
typedef  int u32 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,int) ; 
 int PLATFORM_SPI_CPHA_HIGH ; 
 int PLATFORM_SPI_CPHA_LOW ; 
 int PLATFORM_SPI_CPOL_HIGH ; 
 int PLATFORM_SPI_CPOL_LOW ; 
 int PLATFORM_SPI_MASTER ; 
 int PLATFORM_SPI_SLAVE ; 
 int SPI_FULLDUPLEX ; 
 int SPI_HALFDUPLEX ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int platform_spi_setup (int,int,int,int,int) ; 
 int /*<<< orphan*/  spi ; 
 int* spi_databits ; 
 int* spi_duplex ; 

__attribute__((used)) static int spi_setup( lua_State *L )
{
  int id          = luaL_checkinteger( L, 1 );
  int mode        = luaL_checkinteger( L, 2 );
  int cpol        = luaL_checkinteger( L, 3 );
  int cpha        = luaL_checkinteger( L, 4 );
  int databits    = luaL_checkinteger( L, 5 );
  u32 clock_div   = luaL_checkinteger( L, 6 );
  int duplex_mode = luaL_optinteger( L, 7, SPI_HALFDUPLEX );

  MOD_CHECK_ID( spi, id );

  if (mode != PLATFORM_SPI_SLAVE && mode != PLATFORM_SPI_MASTER) {
    return luaL_error( L, "wrong arg type" );
  }

  if (cpol != PLATFORM_SPI_CPOL_LOW && cpol != PLATFORM_SPI_CPOL_HIGH) {
    return luaL_error( L, "wrong arg type" );
  }

  if (cpha != PLATFORM_SPI_CPHA_LOW && cpha != PLATFORM_SPI_CPHA_HIGH) {
    return luaL_error( L, "wrong arg type" );
  }

  if (databits < 0 || databits > 32) {
    return luaL_error( L, "out of range" );
  }

  if (clock_div == 0) {
    // defaulting to 8 for backward compatibility
    clock_div = 8;
  }

  if (duplex_mode == SPI_HALFDUPLEX || duplex_mode == SPI_FULLDUPLEX)
  {
    spi_duplex[id] = duplex_mode;
  }
  else
  {
    return luaL_error( L, "out of range" );
  }

  spi_databits[id] = databits;

  u32 res = platform_spi_setup(id, mode, cpol, cpha, clock_div);
  lua_pushinteger( L, res );
  return 1;
}