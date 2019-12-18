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
 scalar_t__ PyArg_ParseTuple (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_True ; 

__attribute__((used)) static PyObject *
PLy_plan_status(PyObject *self, PyObject *args)
{
	if (PyArg_ParseTuple(args, ":status"))
	{
		Py_INCREF(Py_True);
		return Py_True;
		/* return PyInt_FromLong(self->status); */
	}
	return NULL;
}