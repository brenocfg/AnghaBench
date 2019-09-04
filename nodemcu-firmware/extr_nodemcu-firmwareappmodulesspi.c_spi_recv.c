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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_spi_send_recv (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi ; 
 int /*<<< orphan*/ * spi_databits ; 

__attribute__((used)) static int spi_recv( lua_State *L )
{
  int id   = luaL_checkinteger( L, 1 );
  int size = luaL_checkinteger( L, 2 ), i;
  int def  = luaL_optinteger( L, 3, 0xffffffff );

  luaL_Buffer b;

  MOD_CHECK_ID( spi, id );
  if (size == 0) {
    return 0;
  }

  luaL_buffinit( L, &b );
  for (i=0; i<size; i++)
  {
    luaL_addchar( &b, ( char )platform_spi_send_recv( id, spi_databits[id], def ) );
  }

  luaL_pushresult( &b );
  return 1;
}