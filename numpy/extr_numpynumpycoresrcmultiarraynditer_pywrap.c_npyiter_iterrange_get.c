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
typedef  int /*<<< orphan*/  npy_intp ;
struct TYPE_3__ {int /*<<< orphan*/ * iter; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  NpyIter_GetIterIndexRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyInt_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *npyiter_iterrange_get(NewNpyArrayIterObject *self)
{
    npy_intp istart = 0, iend = 0;
    PyObject *ret;

    if (self->iter == NULL) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is invalid");
        return NULL;
    }

    NpyIter_GetIterIndexRange(self->iter, &istart, &iend);

    ret = PyTuple_New(2);
    if (ret == NULL) {
        return NULL;
    }

    PyTuple_SET_ITEM(ret, 0, PyInt_FromLong(istart));
    PyTuple_SET_ITEM(ret, 1, PyInt_FromLong(iend));

    return ret;
}