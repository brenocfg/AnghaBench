#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ml_name; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyMethodDef ;

/* Variables and functions */
 int /*<<< orphan*/ * PyCFunction_NewEx (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyModule_GetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyModule_GetNameObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

void add_functions_to_py_module(PyObject *module, PyMethodDef *method_list)
{
	PyObject *dict = PyModule_GetDict(module);
	PyObject *name = PyModule_GetNameObject(module);
	if (!dict || !name) {
		return;
	}
	for (PyMethodDef *ml = method_list; ml->ml_name != NULL; ml++) {
		PyObject *func = PyCFunction_NewEx(ml, module, name);
		if (!func) {
			continue;
		}
		PyDict_SetItemString(dict, ml->ml_name, func);
		Py_DECREF(func);
	}
	Py_DECREF(name);
}