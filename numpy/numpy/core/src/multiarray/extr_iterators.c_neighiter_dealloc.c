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
struct TYPE_6__ {scalar_t__ mode; TYPE_1__* _internal_iter; scalar_t__ constant; } ;
struct TYPE_5__ {int /*<<< orphan*/  ao; } ;
typedef  TYPE_1__ PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_2__ PyArrayNeighborhoodIterObject ;
typedef  int /*<<< orphan*/  PyArrayIterObject ;

/* Variables and functions */
 scalar_t__ NPY_NEIGHBORHOOD_ITER_CONSTANT_PADDING ; 
 scalar_t__ PyArray_ISOBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyDataMem_FREE (scalar_t__) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  array_iter_base_dealloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neighiter_dealloc(PyArrayNeighborhoodIterObject* iter)
{
    if (iter->mode == NPY_NEIGHBORHOOD_ITER_CONSTANT_PADDING) {
        if (PyArray_ISOBJECT(iter->_internal_iter->ao)) {
            Py_DECREF(*(PyObject**)iter->constant);
        }
    }
    PyDataMem_FREE(iter->constant);
    Py_DECREF(iter->_internal_iter);

    array_iter_base_dealloc((PyArrayIterObject*)iter);
    PyArray_free((PyArrayObject*)iter);
}