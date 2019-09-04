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
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Dims ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  NPY_ORDER ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_CORDER ; 
 int /*<<< orphan*/  NpyArg_ParseKeywords (int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_IntpConverter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_Newshape (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_OrderConverter ; 
 int /*<<< orphan*/ * PyArray_View (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 scalar_t__ PyTuple_GET_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PyTuple_Size (int /*<<< orphan*/ *) ; 
 scalar_t__ Py_None ; 
 int /*<<< orphan*/  npy_free_cache_dim_obj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
array_reshape(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    static char *keywords[] = {"order", NULL};
    PyArray_Dims newshape;
    PyObject *ret;
    NPY_ORDER order = NPY_CORDER;
    Py_ssize_t n = PyTuple_Size(args);

    if (!NpyArg_ParseKeywords(kwds, "|O&", keywords,
                PyArray_OrderConverter, &order)) {
        return NULL;
    }

    if (n <= 1) {
        if (n != 0 && PyTuple_GET_ITEM(args, 0) == Py_None) {
            return PyArray_View(self, NULL, NULL);
        }
        if (!PyArg_ParseTuple(args, "O&:reshape", PyArray_IntpConverter,
                              &newshape)) {
            return NULL;
        }
    }
    else {
        if (!PyArray_IntpConverter(args, &newshape)) {
            if (!PyErr_Occurred()) {
                PyErr_SetString(PyExc_TypeError,
                                "invalid shape");
            }
            goto fail;
        }
    }
    ret = PyArray_Newshape(self, &newshape, order);
    npy_free_cache_dim_obj(newshape);
    return ret;

 fail:
    npy_free_cache_dim_obj(newshape);
    return NULL;
}