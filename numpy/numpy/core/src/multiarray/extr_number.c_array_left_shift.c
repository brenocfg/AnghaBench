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
struct TYPE_2__ {int /*<<< orphan*/  left_shift; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  BINOP_GIVE_UP_IF_NEEDED (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/ * PyArray_GenericBinaryFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_inplace_left_shift ; 
 TYPE_1__ n_ops ; 
 int /*<<< orphan*/  nb_lshift ; 
 scalar_t__ try_binary_elide (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
array_left_shift(PyArrayObject *m1, PyObject *m2)
{
    PyObject *res;

    BINOP_GIVE_UP_IF_NEEDED(m1, m2, nb_lshift, array_left_shift);
    if (try_binary_elide(m1, m2, &array_inplace_left_shift, &res, 0)) {
        return res;
    }
    return PyArray_GenericBinaryFunction(m1, m2, n_ops.left_shift);
}