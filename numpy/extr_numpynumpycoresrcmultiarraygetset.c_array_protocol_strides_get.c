#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ PyArray_ISCONTIGUOUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_IntTupleFromIntp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 

__attribute__((used)) static PyObject *
array_protocol_strides_get(PyArrayObject *self)
{
    if (PyArray_ISCONTIGUOUS(self)) {
        Py_RETURN_NONE;
    }
    return PyArray_IntTupleFromIntp(PyArray_NDIM(self), PyArray_STRIDES(self));
}