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
struct TYPE_4__ {scalar_t__ identity; int /*<<< orphan*/ * obj; int /*<<< orphan*/ * identity_value; int /*<<< orphan*/  userloops; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  ptr; int /*<<< orphan*/  core_signature; int /*<<< orphan*/  core_offsets; int /*<<< orphan*/  core_dim_flags; int /*<<< orphan*/  core_dim_sizes; int /*<<< orphan*/  core_dim_ixs; int /*<<< orphan*/  core_num_dims; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyObject_GC_Del (TYPE_1__*) ; 
 int /*<<< orphan*/  PyObject_GC_UnTrack (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUFunc_IdentityValue ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ufunc_dealloc(PyUFuncObject *ufunc)
{
    PyObject_GC_UnTrack((PyObject *)ufunc);
    PyArray_free(ufunc->core_num_dims);
    PyArray_free(ufunc->core_dim_ixs);
    PyArray_free(ufunc->core_dim_sizes);
    PyArray_free(ufunc->core_dim_flags);
    PyArray_free(ufunc->core_offsets);
    PyArray_free(ufunc->core_signature);
    PyArray_free(ufunc->ptr);
    PyArray_free(ufunc->op_flags);
    Py_XDECREF(ufunc->userloops);
    if (ufunc->identity == PyUFunc_IdentityValue) {
        Py_DECREF(ufunc->identity_value);
    }
    if (ufunc->obj != NULL) {
        Py_DECREF(ufunc->obj);
    }
    PyObject_GC_Del(ufunc);
}