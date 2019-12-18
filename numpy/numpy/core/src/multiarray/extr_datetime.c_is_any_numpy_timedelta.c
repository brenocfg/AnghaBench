#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_bool ;
struct TYPE_2__ {scalar_t__ type_num; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ NPY_TIMEDELTA ; 
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 TYPE_1__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_IsScalar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PyDelta_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Timedelta ; 

__attribute__((used)) static npy_bool
is_any_numpy_timedelta(PyObject *obj)
{
    return (PyArray_IsScalar(obj, Timedelta) ||
        (PyArray_Check(obj) && (
            PyArray_DESCR((PyArrayObject *)obj)->type_num == NPY_TIMEDELTA)) ||
        PyDelta_Check(obj));
}