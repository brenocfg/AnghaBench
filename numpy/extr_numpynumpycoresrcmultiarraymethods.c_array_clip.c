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
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PyArray_Clip (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_OutputConverter ; 
 int /*<<< orphan*/ * PyArray_Return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 

__attribute__((used)) static PyObject *
array_clip(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *min = NULL, *max = NULL;
    PyArrayObject *out = NULL;
    static char *kwlist[] = {"min", "max", "out", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOO&:clip", kwlist,
                                     &min,
                                     &max,
                                     PyArray_OutputConverter, &out)) {
        return NULL;
    }
    if (max == NULL && min == NULL) {
        PyErr_SetString(PyExc_ValueError, "One of max or min must be given.");
        return NULL;
    }
    return PyArray_Return((PyArrayObject *)PyArray_Clip(self, min, max, out));
}