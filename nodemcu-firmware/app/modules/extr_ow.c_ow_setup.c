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
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  onewire_init (unsigned int) ; 
 int /*<<< orphan*/  ow ; 

__attribute__((used)) static int ow_setup( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );

  if(id==0)
    return luaL_error( L, "no 1-wire for D0" );

  MOD_CHECK_ID( ow, id );

  onewire_init( id );
  return 0;
}