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
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gpio ; 
 int /*<<< orphan*/  i2c ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ platform_i2c_setup (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_setup( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  unsigned sda = luaL_checkinteger( L, 2 );
  unsigned scl = luaL_checkinteger( L, 3 );

  MOD_CHECK_ID( i2c, id );
  MOD_CHECK_ID( gpio, sda );
  MOD_CHECK_ID( gpio, scl );

  if ( sda == 0 )
    return luaL_error( L, "i2c SDA on D0 is not supported" );

  s32 speed = ( s32 )luaL_checkinteger( L, 4 );
  if ( speed <= 0 )
    return luaL_error( L, "wrong arg range" );
  speed = platform_i2c_setup( id, sda, scl, (u32)speed );
  if ( speed == 0 )
    return luaL_error( L, "failed to initialize i2c %d", id );
  lua_pushinteger( L, speed );
  return 1;
}