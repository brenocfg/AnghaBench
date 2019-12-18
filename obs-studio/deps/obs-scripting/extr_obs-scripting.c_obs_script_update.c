#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ obs_script_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 scalar_t__ OBS_SCRIPT_LANG_LUA ; 
 scalar_t__ OBS_SCRIPT_LANG_PYTHON ; 
 int /*<<< orphan*/  obs_lua_script_update (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_python_script_update (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptr_valid (TYPE_1__*) ; 

void obs_script_update(obs_script_t *script, obs_data_t *settings)
{
	if (!ptr_valid(script))
		return;
#if COMPILE_LUA
	if (script->type == OBS_SCRIPT_LANG_LUA) {
		obs_lua_script_update(script, settings);
	}
#endif
#if COMPILE_PYTHON
	if (script->type == OBS_SCRIPT_LANG_PYTHON) {
		obs_python_script_update(script, settings);
	}
#endif
}