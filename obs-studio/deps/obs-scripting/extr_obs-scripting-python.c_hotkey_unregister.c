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
struct python_obs_callback {int dummy; } ;
struct obs_python_script {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyFunction_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 struct obs_python_script* cur_python_script ; 
 struct python_obs_callback* find_python_obs_callback (struct obs_python_script*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * python_none () ; 
 int /*<<< orphan*/  remove_python_obs_callback (struct python_obs_callback*) ; 

__attribute__((used)) static PyObject *hotkey_unregister(PyObject *self, PyObject *args)
{
	struct obs_python_script *script = cur_python_script;
	PyObject *py_cb = NULL;

	if (!script) {
		PyErr_SetString(PyExc_RuntimeError,
				"No active script, report this to Jim");
		return NULL;
	}

	if (!parse_args(args, "O", &py_cb))
		return python_none();
	if (!py_cb || !PyFunction_Check(py_cb))
		return python_none();

	struct python_obs_callback *cb =
		find_python_obs_callback(script, py_cb);
	if (cb)
		remove_python_obs_callback(cb);

	UNUSED_PARAMETER(self);
	return python_none();
}