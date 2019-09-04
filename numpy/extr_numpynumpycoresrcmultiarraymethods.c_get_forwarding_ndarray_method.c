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
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/ * PyImport_ImportModule (char*) ; 
 int /*<<< orphan*/  PyModule_GetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
get_forwarding_ndarray_method(const char *name)
{
    PyObject *module_methods, *callable;

    /* Get a reference to the function we're calling */
    module_methods = PyImport_ImportModule("numpy.core._methods");
    if (module_methods == NULL) {
        return NULL;
    }
    callable = PyDict_GetItemString(PyModule_GetDict(module_methods), name);
    if (callable == NULL) {
        Py_DECREF(module_methods);
        PyErr_Format(PyExc_RuntimeError,
                "NumPy internal error: could not find function "
                "numpy.core._methods.%s", name);
    }
    else {
        Py_INCREF(callable);
    }
    Py_DECREF(module_methods);
    return callable;
}