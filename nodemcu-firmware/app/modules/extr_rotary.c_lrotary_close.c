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
typedef  int /*<<< orphan*/  DATA ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ROTARY_ALL ; 
 int /*<<< orphan*/  callback_free (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** data ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rotary ; 
 scalar_t__ rotary_close (unsigned int) ; 

__attribute__((used)) static int lrotary_close( lua_State* L )
{
  unsigned int id;

  id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( rotary, id );
  callback_free(L, id, ROTARY_ALL);

  DATA *d = data[id];
  if (d) {
    data[id] = NULL;
    free(d);
  }

  if (rotary_close( id )) {
    return luaL_error( L, "Unable to close switch." );
  }
  return 0;
}