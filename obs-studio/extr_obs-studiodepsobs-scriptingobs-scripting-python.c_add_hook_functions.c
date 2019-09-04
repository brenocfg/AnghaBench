#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyMethodDef ;

/* Variables and functions */
#define  METH_VARARGS 149 
 int /*<<< orphan*/  add_functions_to_py_module (int /*<<< orphan*/ *,TYPE_1__*) ; 
#define  calldata_sceneitem 148 
#define  calldata_source 147 
#define  enum_sources 146 
#define  hotkey_register_frontend 145 
#define  hotkey_unregister 144 
#define  obs_python_add_tick_callback 143 
#define  obs_python_remove_tick_callback 142 
#define  obs_python_signal_handler_connect 141 
#define  obs_python_signal_handler_connect_global 140 
#define  obs_python_signal_handler_disconnect 139 
#define  obs_python_signal_handler_disconnect_global 138 
#define  properties_add_button 137 
#define  property_set_modified_callback 136 
#define  py_script_log 135 
#define  py_script_log_no_endl 134 
#define  remove_current_callback 133 
#define  scene_enum_items 132 
#define  sceneitem_list_release 131 
#define  source_list_release 130 
#define  timer_add 129 
#define  timer_remove 128 

__attribute__((used)) static void add_hook_functions(PyObject *module)
{
	static PyMethodDef funcs[] = {
#define DEF_FUNC(n, c) {n, c, METH_VARARGS, NULL}

		DEF_FUNC("script_log_no_endl", py_script_log_no_endl),
		DEF_FUNC("script_log", py_script_log),
		DEF_FUNC("timer_remove", timer_remove),
		DEF_FUNC("timer_add", timer_add),
		DEF_FUNC("calldata_source", calldata_source),
		DEF_FUNC("calldata_sceneitem", calldata_sceneitem),
		DEF_FUNC("source_list_release", source_list_release),
		DEF_FUNC("sceneitem_list_release", sceneitem_list_release),
		DEF_FUNC("obs_enum_sources", enum_sources),
		DEF_FUNC("obs_scene_enum_items", scene_enum_items),
		DEF_FUNC("obs_remove_tick_callback",
		         obs_python_remove_tick_callback),
		DEF_FUNC("obs_add_tick_callback",
		         obs_python_add_tick_callback),
		DEF_FUNC("signal_handler_disconnect",
		         obs_python_signal_handler_disconnect),
		DEF_FUNC("signal_handler_connect",
		         obs_python_signal_handler_connect),
		DEF_FUNC("signal_handler_disconnect_global",
		         obs_python_signal_handler_disconnect_global),
		DEF_FUNC("signal_handler_connect_global",
		         obs_python_signal_handler_connect_global),
		DEF_FUNC("obs_hotkey_unregister",
			hotkey_unregister),
		DEF_FUNC("obs_hotkey_register_frontend",
			hotkey_register_frontend),
		DEF_FUNC("obs_properties_add_button",
			properties_add_button),
		DEF_FUNC("obs_property_set_modified_callback",
			property_set_modified_callback),
		DEF_FUNC("remove_current_callback",
		         remove_current_callback),

#undef DEF_FUNC
		{0}
	};

	add_functions_to_py_module(module, funcs);
}