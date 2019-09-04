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
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  PyArray_DescrConverter ; 
 scalar_t__ PyArray_SetField (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_setfield(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    PyArray_Descr *dtype = NULL;
    int offset = 0;
    PyObject *value;
    static char *kwlist[] = {"value", "dtype", "offset", 0};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO&|i:setfield", kwlist,
                                     &value,
                                     PyArray_DescrConverter, &dtype,
                                     &offset)) {
        Py_XDECREF(dtype);
        return NULL;
    }

    if (PyArray_SetField(self, dtype, offset, value) < 0) {
        return NULL;
    }
    Py_RETURN_NONE;
}