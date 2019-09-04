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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_TNUMBER ; 
 int /*<<< orphan*/  flash_rom_get_size_byte () ; 
 int /*<<< orphan*/  flash_rom_set_size_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int node_flashsize( lua_State* L )
{
  if (lua_type(L, 1) == LUA_TNUMBER)
  {
    flash_rom_set_size_byte(luaL_checkinteger(L, 1));
  }
  uint32_t sz = flash_rom_get_size_byte();
  lua_pushinteger( L, sz );
  return 1;
}