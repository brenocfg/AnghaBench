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
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* lua_getupvalue (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_iscfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 char* lua_setupvalue (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int auxupvalue (lua_State *L, int get) {
  const char *name;
  int n = luaL_checkint(L, 2);
  luaL_checktype(L, 1, LUA_TFUNCTION);
  if (lua_iscfunction(L, 1)) return 0;  /* cannot touch C upvalues from Lua */
  name = get ? lua_getupvalue(L, 1, n) : lua_setupvalue(L, 1, n);
  if (name == NULL) return 0;
  lua_pushstring(L, name);
  lua_insert(L, -(get+1));
  return get + 1;
}