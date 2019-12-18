#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ npy_intp ;
struct TYPE_4__ {int /*<<< orphan*/ * iter; scalar_t__ finished; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 scalar_t__ NpyIter_GetNOp (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_HasDelayedBufAlloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PySequence_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PySequence_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ npyiter_seq_ass_item (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
npyiter_seq_ass_slice(NewNpyArrayIterObject *self, Py_ssize_t ilow,
                Py_ssize_t ihigh, PyObject *v)
{
    npy_intp nop;
    Py_ssize_t i;

    if (v == NULL) {
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
    nop = NpyIter_GetNOp(self->iter);
    if (ilow < 0) {
        ilow = 0;
    }
    else if (ilow >= nop) {
        ilow = nop-1;
    }
    if (ihigh < ilow) {
        ihigh = ilow;
    }
    else if (ihigh > nop) {
        ihigh = nop;
    }

    if (!PySequence_Check(v) || PySequence_Size(v) != ihigh-ilow) {
        PyErr_SetString(PyExc_ValueError,
                "Wrong size to assign to iterator slice");
        return -1;
    }

    for (i = ilow; i < ihigh ; ++i) {
        PyObject *item = PySequence_GetItem(v, i-ilow);
        if (item == NULL) {
            return -1;
        }
        if (npyiter_seq_ass_item(self, i, item) < 0) {
            Py_DECREF(item);
            return -1;
        }
        Py_DECREF(item);
    }

    return 0;
}