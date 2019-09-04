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
struct TYPE_3__ {int /*<<< orphan*/ ** operands; int /*<<< orphan*/ * iter; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 size_t NpyIter_GetNOp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyTuple_New (size_t) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *npyiter_operands_get(NewNpyArrayIterObject *self)
{
    PyObject *ret;

    npy_intp iop, nop;
    PyArrayObject **operands;

    if (self->iter == NULL) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is invalid");
        return NULL;
    }
    nop = NpyIter_GetNOp(self->iter);
    operands = self->operands;

    ret = PyTuple_New(nop);
    if (ret == NULL) {
        return NULL;
    }
    for (iop = 0; iop < nop; ++iop) {
        PyObject *operand = (PyObject *)operands[iop];

        Py_INCREF(operand);
        PyTuple_SET_ITEM(ret, iop, operand);
    }

    return ret;
}