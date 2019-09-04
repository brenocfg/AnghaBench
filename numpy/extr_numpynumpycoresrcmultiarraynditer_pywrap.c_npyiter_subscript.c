#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  npy_intp ;
struct TYPE_5__ {int /*<<< orphan*/ * iter; scalar_t__ finished; } ;
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  NpyIter_GetNOp (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_HasDelayedBufAlloc (int /*<<< orphan*/ *) ; 
 scalar_t__ NpySlice_GetIndicesEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  PyArray_PyIntAsIntp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 scalar_t__ PyIndex_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PySequence_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySlice_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ error_converting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * npyiter_seq_item (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * npyiter_seq_slice (TYPE_1__*,int,int) ; 

__attribute__((used)) static PyObject *
npyiter_subscript(NewNpyArrayIterObject *self, PyObject *op)
{
    if (self->iter == NULL || self->finished) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is past the end");
        return NULL;
    }

    if (NpyIter_HasDelayedBufAlloc(self->iter)) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator construction used delayed buffer allocation, "
                "and no reset has been done yet");
        return NULL;
    }

    if (PyInt_Check(op) || PyLong_Check(op) ||
                    (PyIndex_Check(op) && !PySequence_Check(op))) {
        npy_intp i = PyArray_PyIntAsIntp(op);
        if (error_converting(i)) {
            return NULL;
        }
        return npyiter_seq_item(self, i);
    }
    else if (PySlice_Check(op)) {
        Py_ssize_t istart = 0, iend = 0, istep = 0, islicelength;
        if (NpySlice_GetIndicesEx(op, NpyIter_GetNOp(self->iter),
                                  &istart, &iend, &istep, &islicelength) < 0) {
            return NULL;
        }
        if (istep != 1) {
            PyErr_SetString(PyExc_ValueError,
                    "Iterator slicing only supports a step of 1");
            return NULL;
        }
        return npyiter_seq_slice(self, istart, iend);
    }

    PyErr_SetString(PyExc_TypeError,
            "invalid index type for iterator indexing");
    return NULL;
}