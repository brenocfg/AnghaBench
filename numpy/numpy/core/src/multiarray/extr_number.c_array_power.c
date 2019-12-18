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
struct TYPE_2__ {int /*<<< orphan*/  power; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  BINOP_GIVE_UP_IF_NEEDED (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/ * PyArray_GenericBinaryFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * Py_NotImplemented ; 
 scalar_t__ fast_scalar_power (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_1__ n_ops ; 
 int /*<<< orphan*/  nb_power ; 

__attribute__((used)) static PyObject *
array_power(PyArrayObject *a1, PyObject *o2, PyObject *modulo)
{
    PyObject *value = NULL;

    if (modulo != Py_None) {
        /* modular exponentiation is not implemented (gh-8804) */
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }

    BINOP_GIVE_UP_IF_NEEDED(a1, o2, nb_power, array_power);
    if (fast_scalar_power(a1, o2, 0, &value) != 0) {
        value = PyArray_GenericBinaryFunction(a1, o2, n_ops.power);
    }
    return value;
}