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
 int /*<<< orphan*/  callback_free (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  callback_set (int /*<<< orphan*/ *,unsigned int,int) ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switec ; 
 scalar_t__ switec_moveto (unsigned int,int) ; 

__attribute__((used)) static int lswitec_moveto( lua_State* L )
{
  unsigned int id;

  id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( switec, id );
  int pos;
  pos = luaL_checkinteger( L, 2 );

  if (lua_gettop(L) >= 3) {
    callback_set(L, id, 3);
  } else {
    callback_free(L, id);
  }

  if (switec_moveto( id, pos )) {
    return luaL_error( L, "Unable to move stepper." );
  }
  return 0;
}