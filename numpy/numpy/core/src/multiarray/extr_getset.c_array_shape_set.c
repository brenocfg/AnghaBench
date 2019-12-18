#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  npy_intp ;
struct TYPE_2__ {int nd; int /*<<< orphan*/ * strides; int /*<<< orphan*/ * dimensions; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayObject_fields ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_ARRAY_C_CONTIGUOUS ; 
 int NPY_ARRAY_F_CONTIGUOUS ; 
 scalar_t__ PyArray_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_Reshape (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_UpdateFlags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 int /*<<< orphan*/  PyExc_MemoryError ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * npy_alloc_cache_dim (int) ; 
 int /*<<< orphan*/  npy_free_cache_dim_array (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
array_shape_set(PyArrayObject *self, PyObject *val)
{
    int nd;
    PyArrayObject *ret;

    if (val == NULL) {
        PyErr_SetString(PyExc_AttributeError,
                "Cannot delete array shape");
        return -1;
    }
    /* Assumes C-order */
    ret = (PyArrayObject *)PyArray_Reshape(self, val);
    if (ret == NULL) {
        return -1;
    }
    if (PyArray_DATA(ret) != PyArray_DATA(self)) {
        Py_DECREF(ret);
        PyErr_SetString(PyExc_AttributeError,
                        "incompatible shape for a non-contiguous "\
                        "array");
        return -1;
    }

    /* Free old dimensions and strides */
    npy_free_cache_dim_array(self);
    nd = PyArray_NDIM(ret);
    ((PyArrayObject_fields *)self)->nd = nd;
    if (nd > 0) {
        /* create new dimensions and strides */
        ((PyArrayObject_fields *)self)->dimensions = npy_alloc_cache_dim(2 * nd);
        if (PyArray_DIMS(self) == NULL) {
            Py_DECREF(ret);
            PyErr_SetString(PyExc_MemoryError,"");
            return -1;
        }
        ((PyArrayObject_fields *)self)->strides = PyArray_DIMS(self) + nd;
        if (nd) {
            memcpy(PyArray_DIMS(self), PyArray_DIMS(ret), nd*sizeof(npy_intp));
            memcpy(PyArray_STRIDES(self), PyArray_STRIDES(ret), nd*sizeof(npy_intp));
        }
    }
    else {
        ((PyArrayObject_fields *)self)->dimensions = NULL;
        ((PyArrayObject_fields *)self)->strides = NULL;
    }
    Py_DECREF(ret);
    PyArray_UpdateFlags(self, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_F_CONTIGUOUS);
    return 0;
}