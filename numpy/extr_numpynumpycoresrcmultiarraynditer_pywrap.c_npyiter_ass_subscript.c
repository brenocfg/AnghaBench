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
 int npyiter_seq_ass_item (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int npyiter_seq_ass_slice (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
npyiter_ass_subscript(NewNpyArrayIterObject *self, PyObject *op,
                        PyObject *value)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError,
                "Cannot delete iterator elements");
        return -1;
    }
    if (self->iter == NULL || self->finished) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is past the end");
        return -1;
    }

    if (NpyIter_HasDelayedBufAlloc(self->iter)) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator construction used delayed buffer allocation, "
                "and no reset has been done yet");
        return -1;
    }

    if (PyInt_Check(op) || PyLong_Check(op) ||
                    (PyIndex_Check(op) && !PySequence_Check(op))) {
        npy_intp i = PyArray_PyIntAsIntp(op);
        if (error_converting(i)) {
            return -1;
        }
        return npyiter_seq_ass_item(self, i, value);
    }
    else if (PySlice_Check(op)) {
        Py_ssize_t istart = 0, iend = 0, istep = 0, islicelength = 0;
        if (NpySlice_GetIndicesEx(op, NpyIter_GetNOp(self->iter),
                                  &istart, &iend, &istep, &islicelength) < 0) {
            return -1;
        }
        if (istep != 1) {
            PyErr_SetString(PyExc_ValueError,
                    "Iterator slice assignment only supports a step of 1");
            return -1;
        }
        return npyiter_seq_ass_slice(self, istart, iend, value);
    }

    PyErr_SetString(PyExc_TypeError,
            "invalid index type for iterator indexing");
    return -1;
}