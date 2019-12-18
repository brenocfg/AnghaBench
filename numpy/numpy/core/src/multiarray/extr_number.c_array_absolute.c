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
struct TYPE_2__ {int /*<<< orphan*/  absolute; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyArray_GenericInplaceUnaryFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyArray_GenericUnaryFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_ISCOMPLEX (int /*<<< orphan*/ *) ; 
 scalar_t__ can_elide_temp_unary (int /*<<< orphan*/ *) ; 
 TYPE_1__ n_ops ; 

__attribute__((used)) static PyObject *
array_absolute(PyArrayObject *m1)
{
    if (can_elide_temp_unary(m1) && !PyArray_ISCOMPLEX(m1)) {
        return PyArray_GenericInplaceUnaryFunction(m1, n_ops.absolute);
    }
    return PyArray_GenericUnaryFunction(m1, n_ops.absolute);
}