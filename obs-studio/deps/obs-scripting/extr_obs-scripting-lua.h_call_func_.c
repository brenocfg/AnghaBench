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
struct obs_lua_script {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int LUA_REFNIL ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 struct obs_lua_script* current_lua_script ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  script_warn (int /*<<< orphan*/ *,char*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool call_func_(lua_State *script, int reg_idx, int args,
			      int rets, const char *func,
			      const char *display_name)
{
	if (reg_idx == LUA_REFNIL)
		return false;

	struct obs_lua_script *data = current_lua_script;

	lua_rawgeti(script, LUA_REGISTRYINDEX, reg_idx);
	lua_insert(script, -1 - args);

	if (lua_pcall(script, args, rets, 0) != 0) {
		script_warn(&data->base, "Failed to call %s for %s: %s", func,
			    display_name, lua_tostring(script, -1));
		lua_pop(script, 1);
		return false;
	}

	return true;
}