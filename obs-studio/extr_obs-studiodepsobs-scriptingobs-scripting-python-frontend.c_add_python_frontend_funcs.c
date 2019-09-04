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
#define  METH_VARARGS 143 
 int /*<<< orphan*/  add_functions_to_py_module (int /*<<< orphan*/ *,TYPE_1__*) ; 
#define  add_save_callback 142 
#define  get_current_profile 141 
#define  get_current_scene 140 
#define  get_current_scene_collection 139 
#define  get_current_transition 138 
#define  get_profiles 137 
#define  get_scene_collections 136 
#define  get_scene_names 135 
#define  get_scenes 134 
#define  get_transitions 133 
#define  remove_save_callback 132 
#define  set_current_profile 131 
#define  set_current_scene 130 
#define  set_current_scene_collection 129 
#define  set_current_transition 128 

void add_python_frontend_funcs(PyObject *module)
{
	static PyMethodDef funcs[] = {
#define DEF_FUNC(c) {"obs_frontend_" #c, c, METH_VARARGS, NULL}

		DEF_FUNC(get_scene_names),
		DEF_FUNC(get_scenes),
		DEF_FUNC(get_current_scene),
		DEF_FUNC(set_current_scene),
		DEF_FUNC(get_transitions),
		DEF_FUNC(get_current_transition),
		DEF_FUNC(set_current_transition),
		DEF_FUNC(get_scene_collections),
		DEF_FUNC(get_current_scene_collection),
		DEF_FUNC(set_current_scene_collection),
		DEF_FUNC(get_profiles),
		DEF_FUNC(get_current_profile),
		DEF_FUNC(set_current_profile),
		DEF_FUNC(remove_save_callback),
		DEF_FUNC(add_save_callback),

#undef DEF_FUNC
		{0}
	};

	add_functions_to_py_module(module, funcs);
}