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
 int NODE_VERSION_MAJOR ; 
 int NODE_VERSION_MINOR ; 
 int NODE_VERSION_REVISION ; 
 int flash_rom_get_mode () ; 
 int flash_rom_get_size_byte () ; 
 int flash_rom_get_speed () ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int spi_flash_get_id () ; 
 int system_get_chip_id () ; 

__attribute__((used)) static int node_info( lua_State* L )
{
  lua_pushinteger(L, NODE_VERSION_MAJOR);
  lua_pushinteger(L, NODE_VERSION_MINOR);
  lua_pushinteger(L, NODE_VERSION_REVISION);
  lua_pushinteger(L, system_get_chip_id());   // chip id
  lua_pushinteger(L, spi_flash_get_id());     // flash id
  lua_pushinteger(L, flash_rom_get_size_byte() / 1024);  // flash size in KB
  lua_pushinteger(L, flash_rom_get_mode());
  lua_pushinteger(L, flash_rom_get_speed());
  return 8;
}