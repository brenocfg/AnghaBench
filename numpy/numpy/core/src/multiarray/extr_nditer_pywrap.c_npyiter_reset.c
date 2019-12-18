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
struct TYPE_4__ {int started; int finished; int /*<<< orphan*/ * iter; int /*<<< orphan*/ * get_multi_index; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 scalar_t__ NPY_SUCCEED ; 
 int /*<<< orphan*/ * NpyIter_GetGetMultiIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_GetIterSize (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_HasMultiIndex (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_Reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 scalar_t__ npyiter_resetbasepointers (TYPE_1__*) ; 

__attribute__((used)) static PyObject *
npyiter_reset(NewNpyArrayIterObject *self)
{
    if (self->iter == NULL) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is invalid");
        return NULL;
    }

    if (NpyIter_Reset(self->iter, NULL) != NPY_SUCCEED) {
        return NULL;
    }
    if (NpyIter_GetIterSize(self->iter) == 0) {
        self->started = 1;
        self->finished = 1;
    }
    else {
        self->started = 0;
        self->finished = 0;
    }

    if (self->get_multi_index == NULL && NpyIter_HasMultiIndex(self->iter)) {
        self->get_multi_index = NpyIter_GetGetMultiIndex(self->iter, NULL);
    }

    /* If there is nesting, the nested iterators should be reset */
    if (npyiter_resetbasepointers(self) != NPY_SUCCEED) {
        return NULL;
    }

    Py_RETURN_NONE;
}