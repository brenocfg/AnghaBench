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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  i2c ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_address (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2c_address( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  int address = luaL_checkinteger( L, 2 );
  int direction = luaL_checkinteger( L, 3 );

  MOD_CHECK_ID( i2c, id );
  if ( address < 0 || address > 127 )
    return luaL_error( L, "wrong arg range" );
  lua_pushboolean( L, platform_i2c_send_address( id, (u16)address, direction ) );
  return 1;
}