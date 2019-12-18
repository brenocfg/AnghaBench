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
struct TYPE_3__ {int numiter; scalar_t__* iters; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayMultiIterObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (scalar_t__) ; 

__attribute__((used)) static PyObject *
arraymultiter_iters_get(PyArrayMultiIterObject *self)
{
    PyObject *res;
    int i, n;

    n = self->numiter;
    res = PyTuple_New(n);
    if (res == NULL) {
        return res;
    }
    for (i = 0; i < n; i++) {
        Py_INCREF(self->iters[i]);
        PyTuple_SET_ITEM(res, i, (PyObject *)self->iters[i]);
    }
    return res;
}