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
struct TYPE_4__ {int started; int finished; int /*<<< orphan*/ * iter; int /*<<< orphan*/ * get_multi_index; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 scalar_t__ NPY_SUCCEED ; 
 int /*<<< orphan*/ * NpyIter_GetGetMultiIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_HasMultiIndex (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_ResetToIterIndexRange (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 scalar_t__ npyiter_resetbasepointers (TYPE_1__*) ; 

__attribute__((used)) static int npyiter_iterrange_set(NewNpyArrayIterObject *self, PyObject *value)
{
    npy_intp istart = 0, iend = 0;

    if (value == NULL) {
        PyErr_SetString(PyExc_AttributeError,
                "Cannot delete nditer iterrange");
        return -1;
    }
    if (self->iter == NULL) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is invalid");
        return -1;
    }

    if (!PyArg_ParseTuple(value, "nn", &istart, &iend)) {
        return -1;
    }

    if (NpyIter_ResetToIterIndexRange(self->iter, istart, iend, NULL)
                                                    != NPY_SUCCEED) {
        return -1;
    }
    if (istart < iend) {
        self->started = self->finished = 0;
    }
    else {
        self->started = self->finished = 1;
    }

    if (self->get_multi_index == NULL && NpyIter_HasMultiIndex(self->iter)) {
        self->get_multi_index = NpyIter_GetGetMultiIndex(self->iter, NULL);
    }

    /* If there is nesting, the nested iterators should be reset */
    if (npyiter_resetbasepointers(self) != NPY_SUCCEED) {
        return -1;
    }

    return 0;
}