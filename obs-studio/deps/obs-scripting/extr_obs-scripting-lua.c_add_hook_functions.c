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
 int /*<<< orphan*/  add_func (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calldata_sceneitem ; 
 int /*<<< orphan*/  calldata_source ; 
 int /*<<< orphan*/  enum_sources ; 
 int /*<<< orphan*/  hook_error ; 
 int /*<<< orphan*/  hook_print ; 
 int /*<<< orphan*/  hotkey_register_frontend ; 
 int /*<<< orphan*/  hotkey_unregister ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_script_log ; 
 int /*<<< orphan*/  obs_lua_add_main_render_callback ; 
 int /*<<< orphan*/  obs_lua_add_tick_callback ; 
 int /*<<< orphan*/  obs_lua_remove_main_render_callback ; 
 int /*<<< orphan*/  obs_lua_remove_tick_callback ; 
 int /*<<< orphan*/  obs_lua_signal_handler_connect ; 
 int /*<<< orphan*/  obs_lua_signal_handler_connect_global ; 
 int /*<<< orphan*/  obs_lua_signal_handler_disconnect ; 
 int /*<<< orphan*/  obs_lua_signal_handler_disconnect_global ; 
 int /*<<< orphan*/  properties_add_button ; 
 int /*<<< orphan*/  property_set_modified_callback ; 
 int /*<<< orphan*/  remove_current_callback ; 
 int /*<<< orphan*/  scene_enum_items ; 
 int /*<<< orphan*/  sceneitem_list_release ; 
 int /*<<< orphan*/  source_enum_filters ; 
 int /*<<< orphan*/  source_list_release ; 
 int /*<<< orphan*/  timer_add ; 
 int /*<<< orphan*/  timer_remove ; 

__attribute__((used)) static void add_hook_functions(lua_State *script)
{
#define add_func(name, func)                     \
	do {                                     \
		lua_pushstring(script, name);    \
		lua_pushcfunction(script, func); \
		lua_rawset(script, -3);          \
	} while (false)

	lua_getglobal(script, "_G");

	add_func("print", hook_print);
	add_func("error", hook_error);

	lua_pop(script, 1);

	/* ------------- */

	lua_getglobal(script, "obslua");

	add_func("script_log", lua_script_log);
	add_func("timer_remove", timer_remove);
	add_func("timer_add", timer_add);
	add_func("obs_enum_sources", enum_sources);
	add_func("obs_source_enum_filters", source_enum_filters);
	add_func("obs_scene_enum_items", scene_enum_items);
	add_func("source_list_release", source_list_release);
	add_func("sceneitem_list_release", sceneitem_list_release);
	add_func("calldata_source", calldata_source);
	add_func("calldata_sceneitem", calldata_sceneitem);
	add_func("obs_add_main_render_callback",
		 obs_lua_add_main_render_callback);
	add_func("obs_remove_main_render_callback",
		 obs_lua_remove_main_render_callback);
	add_func("obs_add_tick_callback", obs_lua_add_tick_callback);
	add_func("obs_remove_tick_callback", obs_lua_remove_tick_callback);
	add_func("signal_handler_connect", obs_lua_signal_handler_connect);
	add_func("signal_handler_disconnect",
		 obs_lua_signal_handler_disconnect);
	add_func("signal_handler_connect_global",
		 obs_lua_signal_handler_connect_global);
	add_func("signal_handler_disconnect_global",
		 obs_lua_signal_handler_disconnect_global);
	add_func("obs_hotkey_unregister", hotkey_unregister);
	add_func("obs_hotkey_register_frontend", hotkey_register_frontend);
	add_func("obs_properties_add_button", properties_add_button);
	add_func("obs_property_set_modified_callback",
		 property_set_modified_callback);
	add_func("remove_current_callback", remove_current_callback);

	lua_pop(script, 1);
#undef add_func
}