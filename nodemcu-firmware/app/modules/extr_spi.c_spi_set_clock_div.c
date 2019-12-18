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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,int) ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  spi ; 
 void* spi_set_clkdiv (int,void*) ; 

__attribute__((used)) static int spi_set_clock_div( lua_State *L )
{
  int id = luaL_checkinteger( L, 1 );

  MOD_CHECK_ID( spi, id );

  u32 clk_div = luaL_checkinteger( L, 2 );

  u32 old_div = spi_set_clkdiv(id, clk_div);

  lua_pushinteger( L, old_div );

  return 1;
}