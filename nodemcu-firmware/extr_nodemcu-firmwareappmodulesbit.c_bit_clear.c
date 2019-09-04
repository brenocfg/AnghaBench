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
typedef  int lua_UInteger ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bit_clear( lua_State* L )
{
  lua_UInteger val = ( lua_UInteger )luaL_checkinteger( L, 1 );
  unsigned total = lua_gettop( L ), i;

  for( i = 2; i <= total; i ++ )
    val &= ~( 1 << ( unsigned )luaL_checkinteger( L, i ) );
  lua_pushinteger( L, ( lua_Integer )val );
  return 1;
}