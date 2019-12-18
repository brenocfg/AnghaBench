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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * PyObject_GetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySlice_New (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_getslice(PyArrayObject *self, PyObject *args)
{
    PyObject *start, *stop, *slice, *result;
    if (!PyArg_ParseTuple(args, "OO:__getslice__", &start, &stop)) {
        return NULL;
    }

    slice = PySlice_New(start, stop, NULL);
    if (slice == NULL) {
        return NULL;
    }

    /* Deliberately delegate to subclasses */
    result = PyObject_GetItem((PyObject *)self, slice);
    Py_DECREF(slice);
    return result;
}