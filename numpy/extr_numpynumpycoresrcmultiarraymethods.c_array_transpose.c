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

/* Variables and functions */
 int /*<<< orphan*/  PyArray_IntpConverter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_Transpose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PyTuple_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  npy_free_cache_dim_obj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
array_transpose(PyArrayObject *self, PyObject *args)
{
    PyObject *shape = Py_None;
    Py_ssize_t n = PyTuple_Size(args);
    PyArray_Dims permute;
    PyObject *ret;

    if (n > 1) {
        shape = args;
    }
    else if (n == 1) {
        shape = PyTuple_GET_ITEM(args, 0);
    }

    if (shape == Py_None) {
        ret = PyArray_Transpose(self, NULL);
    }
    else {
        if (!PyArray_IntpConverter(shape, &permute)) {
            return NULL;
        }
        ret = PyArray_Transpose(self, &permute);
        npy_free_cache_dim_obj(permute);
    }

    return ret;
}