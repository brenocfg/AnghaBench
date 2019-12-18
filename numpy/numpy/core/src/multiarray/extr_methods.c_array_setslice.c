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
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ PyObject_SetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySlice_New (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 

__attribute__((used)) static PyObject *
array_setslice(PyArrayObject *self, PyObject *args)
{
    PyObject *start, *stop, *value, *slice;
    if (!PyArg_ParseTuple(args, "OOO:__setslice__", &start, &stop, &value)) {
        return NULL;
    }

    slice = PySlice_New(start, stop, NULL);
    if (slice == NULL) {
        return NULL;
    }

    /* Deliberately delegate to subclasses */
    if (PyObject_SetItem((PyObject *)self, slice, value) < 0) {
        Py_DECREF(slice);
        return NULL;
    }
    Py_DECREF(slice);
    Py_RETURN_NONE;
}