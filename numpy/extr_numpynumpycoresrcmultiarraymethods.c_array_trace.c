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
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int*,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyArray_DescrConverter2 ; 
 int /*<<< orphan*/  PyArray_OutputConverter ; 
 int /*<<< orphan*/ * PyArray_Return (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_Trace (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int _CHKTYPENUM (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_trace(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    int axis1 = 0, axis2 = 1, offset = 0;
    PyArray_Descr *dtype = NULL;
    PyArrayObject *out = NULL;
    int rtype;
    static char *kwlist[] = {"offset", "axis1", "axis2", "dtype", "out", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iiiO&O&:trace", kwlist,
                                     &offset,
                                     &axis1,
                                     &axis2,
                                     PyArray_DescrConverter2, &dtype,
                                     PyArray_OutputConverter, &out)) {
        Py_XDECREF(dtype);
        return NULL;
    }

    rtype = _CHKTYPENUM(dtype);
    Py_XDECREF(dtype);
    return PyArray_Return((PyArrayObject *)PyArray_Trace(self, offset, axis1, axis2, rtype, out));
}