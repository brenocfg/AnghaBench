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
typedef  int /*<<< orphan*/  npy_bool ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_MAXDIMS ; 
 scalar_t__ NPY_SUCCEED ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **) ; 
 scalar_t__ PyArray_ConvertMultiAxis (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_Squeeze (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_SqueezeSelected (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 

__attribute__((used)) static PyObject *
array_squeeze(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *axis_in = NULL;
    npy_bool axis_flags[NPY_MAXDIMS];

    static char *kwlist[] = {"axis", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O:squeeze", kwlist,
                                     &axis_in)) {
        return NULL;
    }

    if (axis_in == NULL || axis_in == Py_None) {
        return PyArray_Squeeze(self);
    }
    else {
        if (PyArray_ConvertMultiAxis(axis_in, PyArray_NDIM(self),
                                            axis_flags) != NPY_SUCCEED) {
            return NULL;
        }

        return PyArray_SqueezeSelected(self, axis_flags);
    }
}