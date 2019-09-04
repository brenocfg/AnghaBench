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
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  ptr_valid (int /*<<< orphan*/ *) ; 

obs_properties_t *obs_script_get_properties(obs_script_t *script)
{
	obs_properties_t *props = NULL;

	if (!ptr_valid(script))
		return NULL;
#if COMPILE_LUA
	if (script->type == OBS_SCRIPT_LANG_LUA) {
		props = obs_lua_script_get_properties(script);
		goto out;
	}
#endif
#if COMPILE_PYTHON
	if (script->type == OBS_SCRIPT_LANG_PYTHON) {
		props = obs_python_script_get_properties(script);
		goto out;
	}
#endif

out:
	if (!props)
		props = obs_properties_create();
	return props;
}