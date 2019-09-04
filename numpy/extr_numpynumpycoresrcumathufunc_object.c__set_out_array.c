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
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_FailUnlessWriteable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 

__attribute__((used)) static int
_set_out_array(PyObject *obj, PyArrayObject **store)
{
    if (obj == Py_None) {
        /* Translate None to NULL */
        return 0;
    }
    if (PyArray_Check(obj)) {
        /* If it's an array, store it */
        if (PyArray_FailUnlessWriteable((PyArrayObject *)obj,
                                        "output array") < 0) {
            return -1;
        }
        Py_INCREF(obj);
        *store = (PyArrayObject *)obj;

        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "return arrays must be of ArrayType");

    return -1;
}