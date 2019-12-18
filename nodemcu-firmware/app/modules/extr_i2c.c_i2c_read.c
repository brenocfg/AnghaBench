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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  i2c ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int platform_i2c_recv_byte (unsigned int,int) ; 

__attribute__((used)) static int i2c_read( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  u32 size = ( u32 )luaL_checkinteger( L, 2 ), i;
  luaL_Buffer b;
  int data;

  MOD_CHECK_ID( i2c, id );
  if( size == 0 )
    return 0;
  luaL_buffinit( L, &b );
  for( i = 0; i < size; i ++ )
    if( ( data = platform_i2c_recv_byte( id, i < size - 1 ) ) == -1 )
      break;
    else
      luaL_addchar( &b, ( char )data );
  luaL_pushresult( &b );
  return 1;
}