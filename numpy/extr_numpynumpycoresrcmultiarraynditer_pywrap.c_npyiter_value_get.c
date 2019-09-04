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
typedef  int npy_intp ;
struct TYPE_4__ {int /*<<< orphan*/ * iter; scalar_t__ finished; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 int NpyIter_GetNOp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * npyiter_seq_item (TYPE_1__*,int) ; 

__attribute__((used)) static PyObject *npyiter_value_get(NewNpyArrayIterObject *self)
{
    PyObject *ret;

    npy_intp iop, nop;

    if (self->iter == NULL || self->finished) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is past the end");
        return NULL;
    }

    nop = NpyIter_GetNOp(self->iter);

    /* Return an array  or tuple of arrays with the values */
    if (nop == 1) {
        ret = npyiter_seq_item(self, 0);
    }
    else {
        ret = PyTuple_New(nop);
        if (ret == NULL) {
            return NULL;
        }
        for (iop = 0; iop < nop; ++iop) {
            PyObject *a = npyiter_seq_item(self, iop);
            if (a == NULL) {
                Py_DECREF(ret);
                return NULL;
            }
            PyTuple_SET_ITEM(ret, iop, a);
        }
    }

    return ret;
}