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
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onewire_reset (unsigned int) ; 
 int /*<<< orphan*/  ow ; 

__attribute__((used)) static int ow_reset( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( ow, id );
  lua_pushinteger( L, onewire_reset(id) );
  return 1;
}