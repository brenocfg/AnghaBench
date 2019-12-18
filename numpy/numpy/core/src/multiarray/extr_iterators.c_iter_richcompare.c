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
typedef  int /*<<< orphan*/  PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_ResolveWritebackIfCopy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * array_richcompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ iter_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
iter_richcompare(PyArrayIterObject *self, PyObject *other, int cmp_op)
{
    PyArrayObject *new;
    PyObject *ret;
    new = (PyArrayObject *)iter_array(self, NULL);
    if (new == NULL) {
        return NULL;
    }
    ret = array_richcompare(new, other, cmp_op);
    PyArray_ResolveWritebackIfCopy(new);
    Py_DECREF(new);
    return ret;
}