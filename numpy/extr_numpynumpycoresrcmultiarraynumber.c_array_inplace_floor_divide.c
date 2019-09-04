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
struct TYPE_2__ {int /*<<< orphan*/  floor_divide; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  INPLACE_GIVE_UP_IF_NEEDED (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/ * PyArray_GenericInplaceBinaryFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ n_ops ; 
 int /*<<< orphan*/  nb_inplace_floor_divide ; 

__attribute__((used)) static PyObject *
array_inplace_floor_divide(PyArrayObject *m1, PyObject *m2)
{
    INPLACE_GIVE_UP_IF_NEEDED(
            m1, m2, nb_inplace_floor_divide, array_inplace_floor_divide);
    return PyArray_GenericInplaceBinaryFunction(m1, m2,
                                                n_ops.floor_divide);
}