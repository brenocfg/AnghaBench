#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t npy_intp ;
struct TYPE_3__ {int /*<<< orphan*/ * iter; int /*<<< orphan*/  (* get_multi_index ) (int /*<<< orphan*/ *,size_t*) ;scalar_t__ finished; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 int NPY_MAXDIMS ; 
 size_t NpyIter_GetNDim (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_HasDelayedBufAlloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NpyIter_HasMultiIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyInt_FromLong (size_t) ; 
 int /*<<< orphan*/ * PyTuple_New (size_t) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static PyObject *npyiter_multi_index_get(NewNpyArrayIterObject *self)
{
    PyObject *ret;
    npy_intp idim, ndim, multi_index[NPY_MAXDIMS];

    if (self->iter == NULL || self->finished) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is past the end");
        return NULL;
    }

    if (self->get_multi_index != NULL) {
        ndim = NpyIter_GetNDim(self->iter);
        self->get_multi_index(self->iter, multi_index);
        ret = PyTuple_New(ndim);
        if (ret == NULL) {
            return NULL;
        }
        for (idim = 0; idim < ndim; ++idim) {
            PyTuple_SET_ITEM(ret, idim,
                    PyInt_FromLong(multi_index[idim]));
        }
        return ret;
    }
    else {
        if (!NpyIter_HasMultiIndex(self->iter)) {
            PyErr_SetString(PyExc_ValueError,
                    "Iterator is not tracking a multi-index");
            return NULL;
        }
        else if (NpyIter_HasDelayedBufAlloc(self->iter)) {
            PyErr_SetString(PyExc_ValueError,
                    "Iterator construction used delayed buffer allocation, "
                    "and no reset has been done yet");
            return NULL;
        }
        else {
            PyErr_SetString(PyExc_ValueError,
                    "Iterator is in an invalid state");
            return NULL;
        }
    }
}