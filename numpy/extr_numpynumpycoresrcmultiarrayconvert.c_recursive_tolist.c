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
typedef  scalar_t__ npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PyArray_GETITEM (int /*<<< orphan*/ *,char*) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_STRIDE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PyList_New (scalar_t__) ; 
 int /*<<< orphan*/  PyList_SET_ITEM (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
recursive_tolist(PyArrayObject *self, char *dataptr, int startdim)
{
    npy_intp i, n, stride;
    PyObject *ret, *item;

    /* Base case */
    if (startdim >= PyArray_NDIM(self)) {
        return PyArray_GETITEM(self, dataptr);
    }

    n = PyArray_DIM(self, startdim);
    stride = PyArray_STRIDE(self, startdim);

    ret = PyList_New(n);
    if (ret == NULL) {
        return NULL;
    }

    for (i = 0; i < n; ++i) {
        item = recursive_tolist(self, dataptr, startdim+1);
        if (item == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
        PyList_SET_ITEM(ret, i, item);

        dataptr += stride;
    }

    return ret;
}