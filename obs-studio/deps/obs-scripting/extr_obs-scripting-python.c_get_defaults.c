#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  settings; } ;
struct obs_python_script {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libobs_to_py (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  obs_data_t ; 
 int /*<<< orphan*/  py_error () ; 

__attribute__((used)) static void get_defaults(struct obs_python_script *data, PyObject *get_defs)
{
	PyObject *py_settings;
	if (!libobs_to_py(obs_data_t, data->base.settings, false, &py_settings))
		return;

	PyObject *args = Py_BuildValue("(O)", py_settings);
	PyObject *py_ret = PyObject_CallObject(get_defs, args);
	py_error();
	Py_XDECREF(py_ret);
	Py_XDECREF(args);
	Py_XDECREF(py_settings);
}