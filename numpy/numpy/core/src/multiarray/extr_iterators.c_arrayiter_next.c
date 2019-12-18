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
struct TYPE_4__ {scalar_t__ index; scalar_t__ size; int /*<<< orphan*/  ao; int /*<<< orphan*/  dataptr; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_ITER_NEXT (TYPE_1__*) ; 
 int /*<<< orphan*/ * PyArray_ToScalar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
arrayiter_next(PyArrayIterObject *it)
{
    PyObject *ret;

    if (it->index < it->size) {
        ret = PyArray_ToScalar(it->dataptr, it->ao);
        PyArray_ITER_NEXT(it);
        return ret;
    }
    return NULL;
}