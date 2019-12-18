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
 int NPY_MAXARGS ; 
 int /*<<< orphan*/  NPY_PRIORITY ; 
 scalar_t__ PyArray_CheckExact (int /*<<< orphan*/ *) ; 
 double PyArray_GetPriority (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_IsAnyScalar (int /*<<< orphan*/ *) ; 
 scalar_t__ PyCallable_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/ * PyObject_GetAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject*
_find_array_method(PyObject *args, PyObject *method_name)
{
    int i, n_methods;
    PyObject *obj;
    PyObject *with_method[NPY_MAXARGS], *methods[NPY_MAXARGS];
    PyObject *method = NULL;

    n_methods = 0;
    for (i = 0; i < PyTuple_GET_SIZE(args); i++) {
        obj = PyTuple_GET_ITEM(args, i);
        if (PyArray_CheckExact(obj) || PyArray_IsAnyScalar(obj)) {
            continue;
        }
        method = PyObject_GetAttr(obj, method_name);
        if (method) {
            if (PyCallable_Check(method)) {
                with_method[n_methods] = obj;
                methods[n_methods] = method;
                ++n_methods;
            }
            else {
                Py_DECREF(method);
                method = NULL;
            }
        }
        else {
            PyErr_Clear();
        }
    }
    if (n_methods > 0) {
        /* If we have some methods defined, find the one of highest priority */
        method = methods[0];
        if (n_methods > 1) {
            double maxpriority = PyArray_GetPriority(with_method[0],
                                                     NPY_PRIORITY);
            for (i = 1; i < n_methods; ++i) {
                double priority = PyArray_GetPriority(with_method[i],
                                                      NPY_PRIORITY);
                if (priority > maxpriority) {
                    maxpriority = priority;
                    Py_DECREF(method);
                    method = methods[i];
                }
                else {
                    Py_DECREF(methods[i]);
                }
            }
        }
    }
    return method;
}