#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ao; int /*<<< orphan*/  dataptr; } ;
struct TYPE_5__ {int numiter; scalar_t__ index; scalar_t__ size; TYPE_2__** iters; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayMultiIterObject ;
typedef  TYPE_2__ PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_ITER_NEXT (TYPE_2__*) ; 
 int /*<<< orphan*/  PyArray_ToScalar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
arraymultiter_next(PyArrayMultiIterObject *multi)
{
    PyObject *ret;
    int i, n;

    n = multi->numiter;
    ret = PyTuple_New(n);
    if (ret == NULL) {
        return NULL;
    }
    if (multi->index < multi->size) {
        for (i = 0; i < n; i++) {
            PyArrayIterObject *it=multi->iters[i];
            PyTuple_SET_ITEM(ret, i,
                             PyArray_ToScalar(it->dataptr, it->ao));
            PyArray_ITER_NEXT(it);
        }
        multi->index++;
        return ret;
    }
    Py_DECREF(ret);
    return NULL;
}