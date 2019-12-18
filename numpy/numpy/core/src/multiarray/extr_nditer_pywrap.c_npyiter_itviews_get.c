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
typedef  scalar_t__ npy_intp ;
struct TYPE_3__ {int /*<<< orphan*/ * iter; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/ * NpyIter_GetIterView (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ NpyIter_GetNOp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyTuple_New (scalar_t__) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *npyiter_itviews_get(NewNpyArrayIterObject *self)
{
    PyObject *ret;

    npy_intp iop, nop;

    if (self->iter == NULL) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is invalid");
        return NULL;
    }
    nop = NpyIter_GetNOp(self->iter);

    ret = PyTuple_New(nop);
    if (ret == NULL) {
        return NULL;
    }
    for (iop = 0; iop < nop; ++iop) {
        PyArrayObject *view = NpyIter_GetIterView(self->iter, iop);

        if (view == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
        PyTuple_SET_ITEM(ret, iop, (PyObject *)view);
    }

    return ret;
}