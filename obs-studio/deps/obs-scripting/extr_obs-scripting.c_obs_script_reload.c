#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; int loaded; } ;
typedef  TYPE_1__ obs_script_t ;

/* Variables and functions */
 scalar_t__ OBS_SCRIPT_LANG_LUA ; 
 scalar_t__ OBS_SCRIPT_LANG_PYTHON ; 
 int /*<<< orphan*/  clear_call_queue () ; 
 int /*<<< orphan*/  obs_lua_script_load (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_lua_script_unload (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_python_script_load (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_python_script_unload (TYPE_1__*) ; 
 int /*<<< orphan*/  ptr_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  scripting_loaded ; 

bool obs_script_reload(obs_script_t *script)
{
	if (!scripting_loaded)
		return false;
	if (!ptr_valid(script))
		return false;

#if COMPILE_LUA
	if (script->type == OBS_SCRIPT_LANG_LUA) {
		obs_lua_script_unload(script);
		clear_call_queue();
		obs_lua_script_load(script);
		goto out;
	}
#endif
#if COMPILE_PYTHON
	if (script->type == OBS_SCRIPT_LANG_PYTHON) {
		obs_python_script_unload(script);
		clear_call_queue();
		obs_python_script_load(script);
		goto out;
	}
#endif

out:
	return script->loaded;
}