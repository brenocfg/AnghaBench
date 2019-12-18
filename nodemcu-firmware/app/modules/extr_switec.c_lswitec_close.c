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
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  switec ; 
 scalar_t__ switec_close (unsigned int) ; 

__attribute__((used)) static int lswitec_close( lua_State* L )
{
  unsigned int id;

  id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( switec, id );
  callback_free(L, id);
  if (switec_close( id )) {
    return luaL_error( L, "Unable to close stepper." );
  }
  return 0;
}