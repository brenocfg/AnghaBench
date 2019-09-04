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
 int /*<<< orphan*/  generic_reader ; 
 int load_aux (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int lua_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int luaB_load (lua_State *L) {
  int status;
  const char *cname = luaL_optstring(L, 2, "=(load)");
  luaL_checktype(L, 1, LUA_TFUNCTION);
  lua_settop(L, 3);  /* function, eventual name, plus one reserved slot */
  status = lua_load(L, generic_reader, NULL, cname);
  return load_aux(L, status);
}