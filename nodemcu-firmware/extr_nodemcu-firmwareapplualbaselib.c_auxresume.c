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
 int CO_SUS ; 
 int LUA_YIELD ; 
 int costatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_checkstack (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int lua_resume (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setlevel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * statnames ; 

__attribute__((used)) static int auxresume (lua_State *L, lua_State *co, int narg) {
  int status = costatus(L, co);
  if (!lua_checkstack(co, narg))
    luaL_error(L, "too many arguments to resume");
  if (status != CO_SUS) {
    lua_pushfstring(L, "cannot resume %s coroutine", statnames[status]);
    return -1;  /* error flag */
  }
  lua_xmove(L, co, narg);
  lua_setlevel(L, co);
  status = lua_resume(co, narg);
  if (status == 0 || status == LUA_YIELD) {
    int nres = lua_gettop(co);
    if (!lua_checkstack(L, nres + 1))
      luaL_error(L, "too many results to resume");
    lua_xmove(co, L, nres);  /* move yielded values */
    return nres;
  }
  else {
    lua_xmove(co, L, 1);  /* move error message */
    return -1;  /* error flag */
  }
}