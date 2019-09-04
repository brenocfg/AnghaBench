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
struct TYPE_4__ {scalar_t__ finished; scalar_t__ started; int /*<<< orphan*/ * iter; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 int NPY_MAXDIMS ; 
 scalar_t__ NPY_SUCCEED ; 
 scalar_t__ NpyIter_GetNDim (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_GotoMultiIndex (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ NpyIter_HasMultiIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 scalar_t__ PyInt_AsLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PySequence_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PySequence_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ error_converting (scalar_t__) ; 
 scalar_t__ npyiter_resetbasepointers (TYPE_1__*) ; 

__attribute__((used)) static int
npyiter_multi_index_set(NewNpyArrayIterObject *self, PyObject *value)
{
    npy_intp idim, ndim, multi_index[NPY_MAXDIMS];

    if (value == NULL) {
        PyErr_SetString(PyExc_AttributeError,
                "Cannot delete nditer multi_index");
        return -1;
    }
    if (self->iter == NULL) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is invalid");
        return -1;
    }

    if (NpyIter_HasMultiIndex(self->iter)) {
        ndim = NpyIter_GetNDim(self->iter);
        if (!PySequence_Check(value)) {
            PyErr_SetString(PyExc_ValueError,
                    "multi_index must be set with a sequence");
            return -1;
        }
        if (PySequence_Size(value) != ndim) {
            PyErr_SetString(PyExc_ValueError,
                    "Wrong number of indices");
            return -1;
        }
        for (idim = 0; idim < ndim; ++idim) {
            PyObject *v = PySequence_GetItem(value, idim);
            multi_index[idim] = PyInt_AsLong(v);
            if (error_converting(multi_index[idim])) {
                Py_XDECREF(v);
                return -1;
            }
        }
        if (NpyIter_GotoMultiIndex(self->iter, multi_index) != NPY_SUCCEED) {
            return -1;
        }
        self->started = 0;
        self->finished = 0;

        /* If there is nesting, the nested iterators should be reset */
        if (npyiter_resetbasepointers(self) != NPY_SUCCEED) {
            return -1;
        }

        return 0;
    }
    else {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is not tracking a multi-index");
        return -1;
    }
}