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

/* Variables and functions */
 scalar_t__ PyArray_CheckExact (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyCallable_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/ * PyObject_GetAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
_get_output_array_method(PyObject *obj, PyObject *method,
                         PyObject *input_method) {
    if (obj != Py_None) {
        PyObject *ometh;

        if (PyArray_CheckExact(obj)) {
            /*
             * No need to wrap regular arrays - None signals to not call
             * wrap/prepare at all
             */
            Py_RETURN_NONE;
        }

        ometh = PyObject_GetAttr(obj, method);
        if (ometh == NULL) {
            PyErr_Clear();
        }
        else if (!PyCallable_Check(ometh)) {
            Py_DECREF(ometh);
        }
        else {
            /* Use the wrap/prepare method of the output if it's callable */
            return ometh;
        }
    }

    /* Fall back on the input's wrap/prepare */
    Py_XINCREF(input_method);
    return input_method;
}