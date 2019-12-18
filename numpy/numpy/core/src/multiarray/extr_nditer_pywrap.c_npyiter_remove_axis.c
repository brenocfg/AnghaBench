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
struct TYPE_4__ {int started; int finished; int /*<<< orphan*/ * iter; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 scalar_t__ NPY_SUCCEED ; 
 scalar_t__ NpyIter_GetIterSize (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_RemoveAxis (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 scalar_t__ npyiter_cache_values (TYPE_1__*) ; 

__attribute__((used)) static PyObject *
npyiter_remove_axis(NewNpyArrayIterObject *self, PyObject *args)
{
    int axis = 0;

    if (self->iter == NULL) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is invalid");
        return NULL;
    }

    if (!PyArg_ParseTuple(args, "i:remove_axis", &axis)) {
        return NULL;
    }

    if (NpyIter_RemoveAxis(self->iter, axis) != NPY_SUCCEED) {
        return NULL;
    }
    /* RemoveAxis invalidates cached values */
    if (npyiter_cache_values(self) < 0) {
        return NULL;
    }
    /* RemoveAxis also resets the iterator */
    if (NpyIter_GetIterSize(self->iter) == 0) {
        self->started = 1;
        self->finished = 1;
    }
    else {
        self->started = 0;
        self->finished = 0;
    }

    Py_RETURN_NONE;
}