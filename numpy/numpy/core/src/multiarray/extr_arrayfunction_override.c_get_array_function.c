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
 int /*<<< orphan*/ * PyArray_LookupSpecial (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_ndarray_array_function () ; 

__attribute__((used)) static PyObject *
get_array_function(PyObject *obj)
{
    static PyObject *ndarray_array_function = NULL;
    PyObject *array_function;

    if (ndarray_array_function == NULL) {
        ndarray_array_function = get_ndarray_array_function();
    }

    /* Fast return for ndarray */
    if (PyArray_CheckExact(obj)) {
        Py_INCREF(ndarray_array_function);
        return ndarray_array_function;
    }

    array_function = PyArray_LookupSpecial(obj, "__array_function__");
    if (array_function == NULL && PyErr_Occurred()) {
        PyErr_Clear(); /* TODO[gh-14801]: propagate crashes during attribute access? */
    }

    return array_function;
}