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
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_MAXDIMS ; 
 scalar_t__ PyArray_FailUnlessWriteable (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PyArray_MultiIndexSetItem (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int PyArray_PyIntAsIntp (int /*<<< orphan*/ *) ; 
 int* PyArray_SHAPE (int /*<<< orphan*/ *) ; 
 int PyArray_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 scalar_t__ PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 scalar_t__ check_and_adjust_index (int*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ error_converting (int) ; 

__attribute__((used)) static PyObject *
array_setscalar(PyArrayObject *self, PyObject *args)
{
    npy_intp multi_index[NPY_MAXDIMS];
    int n = PyTuple_GET_SIZE(args) - 1;
    int idim, ndim = PyArray_NDIM(self);
    PyObject *obj;

    if (n < 0) {
        PyErr_SetString(PyExc_ValueError,
                "itemset must have at least one argument");
        return NULL;
    }
    if (PyArray_FailUnlessWriteable(self, "assignment destination") < 0) {
        return NULL;
    }

    obj = PyTuple_GET_ITEM(args, n);

    /* If there is a tuple as a single argument, treat it as the argument */
    if (n == 1 && PyTuple_Check(PyTuple_GET_ITEM(args, 0))) {
        args = PyTuple_GET_ITEM(args, 0);
        n = PyTuple_GET_SIZE(args);
    }

    if (n == 0) {
        if (PyArray_SIZE(self) == 1) {
            for (idim = 0; idim < ndim; ++idim) {
                multi_index[idim] = 0;
            }
        }
        else {
            PyErr_SetString(PyExc_ValueError,
                    "can only convert an array of size 1 to a Python scalar");
        }
    }
    /* Special case of C-order flat indexing... :| */
    else if (n == 1 && ndim != 1) {
        npy_intp *shape = PyArray_SHAPE(self);
        npy_intp value, size = PyArray_SIZE(self);

        value = PyArray_PyIntAsIntp(PyTuple_GET_ITEM(args, 0));
        if (error_converting(value)) {
            return NULL;
        }

        if (check_and_adjust_index(&value, size, -1, NULL) < 0) {
            return NULL;
        }

        /* Convert the flat index into a multi-index */
        for (idim = ndim-1; idim >= 0; --idim) {
            multi_index[idim] = value % shape[idim];
            value /= shape[idim];
        }
    }
    /* A multi-index tuple */
    else if (n == ndim) {
        npy_intp value;

        for (idim = 0; idim < ndim; ++idim) {
            value = PyArray_PyIntAsIntp(PyTuple_GET_ITEM(args, idim));
            if (error_converting(value)) {
                return NULL;
            }
            multi_index[idim] = value;
        }
    }
    else {
        PyErr_SetString(PyExc_ValueError,
                "incorrect number of indices for array");
        return NULL;
    }

    if (PyArray_MultiIndexSetItem(self, multi_index, obj) < 0) {
        return NULL;
    }
    else {
        Py_RETURN_NONE;
    }
}