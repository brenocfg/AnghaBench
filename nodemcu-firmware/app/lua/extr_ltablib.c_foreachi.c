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
 int aux_getn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checkanyfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int foreachi (lua_State *L) {
  int i;
  int n = aux_getn(L, 1);
  luaL_checkanyfunction(L, 2);
  for (i=1; i <= n; i++) {
    lua_pushvalue(L, 2);  /* function */
    lua_pushinteger(L, i);  /* 1st argument */
    lua_rawgeti(L, 1, i);  /* 2nd argument */
    lua_call(L, 2, 1);
    if (!lua_isnil(L, -1))
      return 1;
    lua_pop(L, 1);  /* remove nil result */
  }
  return 0;
}