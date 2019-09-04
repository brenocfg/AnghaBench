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
struct obs_python_script {int /*<<< orphan*/  save; } ;
struct TYPE_3__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  loaded; } ;
typedef  TYPE_1__ obs_script_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 struct obs_python_script* cur_python_script ; 
 scalar_t__ libobs_to_py (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lock_python () ; 
 int /*<<< orphan*/  obs_data_t ; 
 int /*<<< orphan*/  py_error () ; 
 int /*<<< orphan*/  python_loaded ; 
 int /*<<< orphan*/  unlock_python () ; 

void obs_python_script_save(obs_script_t *s)
{
	struct obs_python_script *data = (struct obs_python_script *)s;

	if (!s->loaded || !python_loaded)
		return;
	if (!data->save)
		return;

	lock_python();
	cur_python_script = data;

	PyObject *py_settings;
	if (libobs_to_py(obs_data_t, s->settings, false, &py_settings)) {
		PyObject *args = Py_BuildValue("(O)", py_settings);
		PyObject *ret = PyObject_CallObject(data->save, args);
		py_error();
		Py_XDECREF(ret);
		Py_XDECREF(args);
		Py_XDECREF(py_settings);
	}

	cur_python_script = NULL;
	unlock_python();
}