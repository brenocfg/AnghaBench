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
typedef  int /*<<< orphan*/  npy_intp ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ARRAY_OWNDATA ; 
 scalar_t__ NPY_SIZEOF_PYARRAYOBJECT ; 
 scalar_t__ PyArray_CHKFLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_NBYTES (int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromSsize_t (scalar_t__) ; 

__attribute__((used)) static PyObject *
array_sizeof(PyArrayObject *self)
{
    /* object + dimension and strides */
    Py_ssize_t nbytes = NPY_SIZEOF_PYARRAYOBJECT +
        PyArray_NDIM(self) * sizeof(npy_intp) * 2;
    if (PyArray_CHKFLAGS(self, NPY_ARRAY_OWNDATA)) {
        nbytes += PyArray_NBYTES(self);
    }
    return PyLong_FromSsize_t(nbytes);
}