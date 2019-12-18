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
 int /*<<< orphan*/  add_event_callback ; 
 int /*<<< orphan*/  add_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_save_callback ; 
 int /*<<< orphan*/  get_current_profile ; 
 int /*<<< orphan*/  get_current_scene ; 
 int /*<<< orphan*/  get_current_scene_collection ; 
 int /*<<< orphan*/  get_current_transition ; 
 int /*<<< orphan*/  get_profiles ; 
 int /*<<< orphan*/  get_scene_collections ; 
 int /*<<< orphan*/  get_scene_names ; 
 int /*<<< orphan*/  get_scenes ; 
 int /*<<< orphan*/  get_transitions ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  remove_event_callback ; 
 int /*<<< orphan*/  remove_save_callback ; 
 int /*<<< orphan*/  set_current_profile ; 
 int /*<<< orphan*/  set_current_scene ; 
 int /*<<< orphan*/  set_current_scene_collection ; 
 int /*<<< orphan*/  set_current_transition ; 

void add_lua_frontend_funcs(lua_State *script)
{
	lua_getglobal(script, "obslua");

#define add_func(name)                                         \
	do {                                                   \
		lua_pushstring(script, "obs_frontend_" #name); \
		lua_pushcfunction(script, name);               \
		lua_rawset(script, -3);                        \
	} while (false)

	add_func(get_scene_names);
	add_func(get_scenes);
	add_func(get_current_scene);
	add_func(set_current_scene);
	add_func(get_transitions);
	add_func(get_current_transition);
	add_func(set_current_transition);
	add_func(get_scene_collections);
	add_func(get_current_scene_collection);
	add_func(set_current_scene_collection);
	add_func(get_profiles);
	add_func(get_current_profile);
	add_func(set_current_profile);
	add_func(remove_event_callback);
	add_func(add_event_callback);
	add_func(remove_save_callback);
	add_func(add_save_callback);
#undef add_func

	lua_pop(script, 1);
}