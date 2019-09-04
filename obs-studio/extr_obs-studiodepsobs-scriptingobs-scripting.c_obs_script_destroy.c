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
typedef  int /*<<< orphan*/  obs_script_t ;

/* Variables and functions */

void obs_script_destroy(obs_script_t *script)
{
	if (!script)
		return;

#if COMPILE_LUA
	if (script->type == OBS_SCRIPT_LANG_LUA) {
		obs_lua_script_unload(script);
		obs_lua_script_destroy(script);
		return;
	}
#endif
#if COMPILE_PYTHON
	if (script->type == OBS_SCRIPT_LANG_PYTHON) {
		obs_python_script_unload(script);
		obs_python_script_destroy(script);
		return;
	}
#endif
}