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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 scalar_t__ LUAL_BUFFERSIZE ; 
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  luaL_addsize (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_prepbuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onewire_read_bytes (unsigned int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ow ; 

__attribute__((used)) static int ow_read_bytes( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( ow, id );
  u32 size = ( u32 )luaL_checkinteger( L, 2 );
  if( size == 0 )
    return 0;

  luaL_argcheck(L, size <= LUAL_BUFFERSIZE, 2, "Attempt to read too many characters");

  luaL_Buffer b;
  luaL_buffinit( L, &b );
  char *p = luaL_prepbuffer(&b);

  onewire_read_bytes(id, (uint8_t *)p, size);

  luaL_addsize(&b, size);
  luaL_pushresult( &b );
  return 1;
}