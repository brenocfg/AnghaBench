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
 scalar_t__ PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (scalar_t__) ; 

__attribute__((used)) static PyObject *
array_descr_get(PyArrayObject *self)
{
    Py_INCREF(PyArray_DESCR(self));
    return (PyObject *)PyArray_DESCR(self);
}