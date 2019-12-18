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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * obs_lua_script_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_python_script_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptr_valid (char const*) ; 
 int /*<<< orphan*/  scripting_loaded ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

obs_script_t *obs_script_create(const char *path, obs_data_t *settings)
{
	obs_script_t *script = NULL;
	const char *ext;

	if (!scripting_loaded)
		return NULL;
	if (!ptr_valid(path))
		return NULL;

	ext = strrchr(path, '.');
	if (!ext)
		return NULL;

#if COMPILE_LUA
	if (strcmp(ext, ".lua") == 0) {
		script = obs_lua_script_create(path, settings);
	} else
#endif
#if COMPILE_PYTHON
		if (strcmp(ext, ".py") == 0) {
		script = obs_python_script_create(path, settings);
	} else
#endif
	{
		blog(LOG_WARNING, "Unsupported/unknown script type: %s", path);
	}

	return script;
}