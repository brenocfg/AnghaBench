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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switec ; 
 scalar_t__ switec_getpos (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lswitec_getpos( lua_State* L )
{
  unsigned int id;

  id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( switec, id );
  int32_t pos;
  int32_t dir;
  int32_t target;
  if (switec_getpos( id, &pos, &dir, &target )) {
    return luaL_error( L, "Unable to get position." );
  }
  lua_pushnumber(L, pos);
  lua_pushnumber(L, dir);
  return 2;
}