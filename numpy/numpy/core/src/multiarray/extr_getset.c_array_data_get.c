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
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_ISONESEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISWRITEABLE (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NBYTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyBuffer_FromObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyBuffer_FromReadWriteObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 int /*<<< orphan*/ * PyMemoryView_FromObject (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_data_get(PyArrayObject *self)
{
#if defined(NPY_PY3K)
    return PyMemoryView_FromObject((PyObject *)self);
#else
    npy_intp nbytes;
    if (!(PyArray_ISONESEGMENT(self))) {
        PyErr_SetString(PyExc_AttributeError, "cannot get single-"\
                        "segment buffer for discontiguous array");
        return NULL;
    }
    nbytes = PyArray_NBYTES(self);
    if (PyArray_ISWRITEABLE(self)) {
        return PyBuffer_FromReadWriteObject((PyObject *)self, 0, (Py_ssize_t) nbytes);
    }
    else {
        return PyBuffer_FromObject((PyObject *)self, 0, (Py_ssize_t) nbytes);
    }
#endif
}