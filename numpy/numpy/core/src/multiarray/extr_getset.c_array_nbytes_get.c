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
 scalar_t__ NPY_MAX_LONG ; 
 scalar_t__ NPY_MIN_LONG ; 
 scalar_t__ PyArray_NBYTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyInt_FromLong (long) ; 
 int /*<<< orphan*/ * PyLong_FromLongLong (scalar_t__) ; 

__attribute__((used)) static PyObject *
array_nbytes_get(PyArrayObject *self)
{
    npy_intp nbytes = PyArray_NBYTES(self);
#if NPY_SIZEOF_INTP <= NPY_SIZEOF_LONG
    return PyInt_FromLong((long) nbytes);
#else
    if (nbytes > NPY_MAX_LONG || nbytes < NPY_MIN_LONG) {
        return PyLong_FromLongLong(nbytes);
    }
    else {
        return PyInt_FromLong((long) nbytes);
    }
#endif
}