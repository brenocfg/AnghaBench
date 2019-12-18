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
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handler_call_die (char const*) ; 

__attribute__((used)) static void call_object(PyObject *handler, PyObject *args, const char *die_msg)
{
	PyObject *retval;

	retval = PyObject_CallObject(handler, args);
	if (retval == NULL)
		handler_call_die(die_msg);
	Py_DECREF(retval);
}