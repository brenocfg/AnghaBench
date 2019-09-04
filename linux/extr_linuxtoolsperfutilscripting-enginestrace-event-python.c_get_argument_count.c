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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ _PyLong_AsLong (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_argument_count(PyObject *handler)
{
	int arg_count = 0;

	/*
	 * The attribute for the code object is func_code in Python 2,
	 * whereas it is __code__ in Python 3.0+.
	 */
	PyObject *code_obj = PyObject_GetAttrString(handler,
		"func_code");
	if (PyErr_Occurred()) {
		PyErr_Clear();
		code_obj = PyObject_GetAttrString(handler,
			"__code__");
	}
	PyErr_Clear();
	if (code_obj) {
		PyObject *arg_count_obj = PyObject_GetAttrString(code_obj,
			"co_argcount");
		if (arg_count_obj) {
			arg_count = (int) _PyLong_AsLong(arg_count_obj);
			Py_DECREF(arg_count_obj);
		}
		Py_DECREF(code_obj);
	}
	return arg_count;
}