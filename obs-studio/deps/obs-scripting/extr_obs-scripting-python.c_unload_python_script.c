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
struct obs_python_script {int /*<<< orphan*/ * module; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 struct obs_python_script* cur_python_script ; 
 scalar_t__ py_error () ; 

__attribute__((used)) static void unload_python_script(struct obs_python_script *data)
{
	PyObject *py_module = data->module;
	PyObject *py_func = NULL;
	PyObject *py_ret = NULL;

	cur_python_script = data;

	py_func = PyObject_GetAttrString(py_module, "script_unload");
	if (PyErr_Occurred() || !py_func) {
		PyErr_Clear();
		goto fail;
	}

	py_ret = PyObject_CallObject(py_func, NULL);
	if (py_error())
		goto fail;

fail:
	Py_XDECREF(py_ret);
	Py_XDECREF(py_func);

	cur_python_script = NULL;
}