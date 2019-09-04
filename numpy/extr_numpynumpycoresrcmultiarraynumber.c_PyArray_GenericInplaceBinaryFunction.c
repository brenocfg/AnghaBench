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
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_NotImplemented ; 

__attribute__((used)) static PyObject *
PyArray_GenericInplaceBinaryFunction(PyArrayObject *m1,
                                     PyObject *m2, PyObject *op)
{
    if (op == NULL) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    return PyObject_CallFunctionObjArgs(op, m1, m2, m1, NULL);
}