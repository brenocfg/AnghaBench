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
struct TYPE_2__ {int /*<<< orphan*/  extra; } ;
struct python_obs_callback {TYPE_1__ base; } ;
struct obs_python_script {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyFunction_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 struct python_obs_callback* add_python_obs_callback (struct obs_python_script*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calldata_set_ptr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  calldata_signal_callback_global ; 
 struct obs_python_script* cur_python_script ; 
 int handler ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  py_to_libobs (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * python_none () ; 
 int /*<<< orphan*/  signal_handler_connect_global (int,int /*<<< orphan*/ ,struct python_obs_callback*) ; 
 int signal_handler_t ; 

__attribute__((used)) static PyObject *obs_python_signal_handler_connect_global(PyObject *self,
							  PyObject *args)
{
	struct obs_python_script *script = cur_python_script;
	PyObject *py_sh = NULL;
	PyObject *py_cb = NULL;

	if (!script) {
		PyErr_SetString(PyExc_RuntimeError,
				"No active script, report this to Jim");
		return NULL;
	}

	UNUSED_PARAMETER(self);

	signal_handler_t *handler;

	if (!parse_args(args, "OO", &py_sh, &py_cb))
		return python_none();

	if (!py_to_libobs(signal_handler_t, py_sh, &handler))
		return python_none();
	if (!py_cb || !PyFunction_Check(py_cb))
		return python_none();

	struct python_obs_callback *cb = add_python_obs_callback(script, py_cb);
	calldata_set_ptr(&cb->base.extra, "handler", handler);
	signal_handler_connect_global(handler, calldata_signal_callback_global,
				      cb);
	return python_none();
}