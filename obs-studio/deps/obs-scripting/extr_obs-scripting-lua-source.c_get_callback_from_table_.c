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
 int LUA_REFNIL ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*,char const*) ; 

__attribute__((used)) static inline void get_callback_from_table_(lua_State *script, int idx,
					    const char *name, int *p_reg_idx,
					    const char *func)
{
	*p_reg_idx = LUA_REFNIL;

	lua_pushstring(script, name);
	lua_gettable(script, idx - 1);
	if (!lua_isfunction(script, -1)) {
		if (!lua_isnil(script, -1)) {
			warn("%s: item '%s' is not a function", func, name);
		}
		lua_pop(script, 1);
	} else {
		*p_reg_idx = luaL_ref(script, LUA_REGISTRYINDEX);
	}
}