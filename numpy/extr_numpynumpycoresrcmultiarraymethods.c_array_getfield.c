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
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  PyArray_DescrConverter ; 
 int /*<<< orphan*/ * PyArray_GetField (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_getfield(PyArrayObject *self, PyObject *args, PyObject *kwds)
{

    PyArray_Descr *dtype = NULL;
    int offset = 0;
    static char *kwlist[] = {"dtype", "offset", 0};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&|i:getfield", kwlist,
                                     PyArray_DescrConverter, &dtype,
                                     &offset)) {
        Py_XDECREF(dtype);
        return NULL;
    }

    return PyArray_GetField(self, dtype, offset);
}