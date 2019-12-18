#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  finished; int /*<<< orphan*/  started; int /*<<< orphan*/ * iter; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/ * NpyIter_Copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NpyIter_Type ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 scalar_t__ npyiter_cache_values (TYPE_1__*) ; 
 scalar_t__ npyiter_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
npyiter_copy(NewNpyArrayIterObject *self)
{
    NewNpyArrayIterObject *iter;

    if (self->iter == NULL) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator is invalid");
        return NULL;
    }

    /* Allocate the iterator */
    iter = (NewNpyArrayIterObject *)npyiter_new(&NpyIter_Type, NULL, NULL);
    if (iter == NULL) {
        return NULL;
    }

    /* Copy the C iterator */
    iter->iter = NpyIter_Copy(self->iter);
    if (iter->iter == NULL) {
        Py_DECREF(iter);
        return NULL;
    }

    /* Cache some values for the member functions to use */
    if (npyiter_cache_values(iter) < 0) {
        Py_DECREF(iter);
        return NULL;
    }

    iter->started = self->started;
    iter->finished = self->finished;

    return (PyObject *)iter;
}