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
 int /*<<< orphan*/ * PyObject_Call (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
forward_ndarray_method(PyArrayObject *self, PyObject *args, PyObject *kwds,
                            PyObject *forwarding_callable)
{
    PyObject *sargs, *ret;
    int i, n;

    /* Combine 'self' and 'args' together into one tuple */
    n = PyTuple_GET_SIZE(args);
    sargs = PyTuple_New(n + 1);
    if (sargs == NULL) {
        return NULL;
    }
    Py_INCREF(self);
    PyTuple_SET_ITEM(sargs, 0, (PyObject *)self);
    for (i = 0; i < n; ++i) {
        PyObject *item = PyTuple_GET_ITEM(args, i);
        Py_INCREF(item);
        PyTuple_SET_ITEM(sargs, i+1, item);
    }

    /* Call the function and return */
    ret = PyObject_Call(forwarding_callable, sargs, kwds);
    Py_DECREF(sargs);
    return ret;
}