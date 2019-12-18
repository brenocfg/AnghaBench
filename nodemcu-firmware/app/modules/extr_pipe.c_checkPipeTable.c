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
typedef  int /*<<< orphan*/  buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  LROT_TABLEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ LUA_TTABLE ; 
 int /*<<< orphan*/ * checkPipeUD (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_typerror (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushrotable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_rawequal (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * newPipeUD (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pipe_meta ; 

__attribute__((used)) static buffer_t *checkPipeTable (lua_State *L, int tbl, int head) {//[-0, +0, v]
  int m = lua_gettop(L), n = lua_objlen(L, tbl);
  if (lua_type(L, tbl) == LUA_TTABLE && lua_getmetatable(L, tbl)) {
    lua_pushrotable(L, LROT_TABLEREF(pipe_meta));/* push comparison metatable */
    if (lua_rawequal(L, -1, -2)) {                       /* check these match */
      buffer_t *ud;
      if (n == 0) {
        ud = head ? NULL : newPipeUD(L, tbl, 1);
      } else {
        int i = head ? 1 : n;                   /* point to head or tail of T */
        lua_rawgeti(L, tbl, i);                               /* and fetch UD */
        ud = checkPipeUD(L, -1);
      }
      lua_settop(L, m);
      return ud;                            /* and return ptr to buffer_t rec */
    }
  }
  luaL_typerror(L, tbl, "pipe table");
  return NULL;                               /* NORETURN avoid compiler error */
}