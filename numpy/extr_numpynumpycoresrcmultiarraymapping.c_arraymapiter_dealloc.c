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
struct TYPE_4__ {int /*<<< orphan*/ * extra_op_iter; int /*<<< orphan*/ * subspace_iter; int /*<<< orphan*/ * outer; int /*<<< orphan*/  extra_op_dtype; int /*<<< orphan*/  extra_op; int /*<<< orphan*/  subspace; int /*<<< orphan*/  ait; int /*<<< orphan*/  array; } ;
typedef  TYPE_1__ PyArrayMapIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  NpyIter_Deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ResolveWritebackIfCopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_free (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arraymapiter_dealloc(PyArrayMapIterObject *mit)
{
    PyArray_ResolveWritebackIfCopy(mit->array);
    Py_XDECREF(mit->array);
    Py_XDECREF(mit->ait);
    Py_XDECREF(mit->subspace);
    Py_XDECREF(mit->extra_op);
    Py_XDECREF(mit->extra_op_dtype);
    if (mit->outer != NULL) {
        NpyIter_Deallocate(mit->outer);
    }
    if (mit->subspace_iter != NULL) {
        NpyIter_Deallocate(mit->subspace_iter);
    }
    if (mit->extra_op_iter != NULL) {
        NpyIter_Deallocate(mit->extra_op_iter);
    }
    PyArray_free(mit);
}