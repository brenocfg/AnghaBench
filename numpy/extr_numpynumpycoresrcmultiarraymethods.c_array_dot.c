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
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyArray_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_MatrixProduct2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_Return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * Py_None ; 

__attribute__((used)) static PyObject *
array_dot(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *a = (PyObject *)self, *b, *o = NULL;
    PyArrayObject *ret;
    char* kwlist[] = {"b", "out", NULL };


    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|O:dot", kwlist, &b, &o)) {
        return NULL;
    }

    if (o != NULL) {
        if (o == Py_None) {
            o = NULL;
        }
        else if (!PyArray_Check(o)) {
            PyErr_SetString(PyExc_TypeError,
                            "'out' must be an array");
            return NULL;
        }
    }
    ret = (PyArrayObject *)PyArray_MatrixProduct2(a, b, (PyArrayObject *)o);
    return PyArray_Return(ret);
}