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
typedef  int /*<<< orphan*/  PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_cache_import (char*,char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
raise_binary_type_reso_error(PyUFuncObject *ufunc, PyArrayObject **operands) {
    static PyObject *exc_type = NULL;
    PyObject *exc_value;

    npy_cache_import(
        "numpy.core._exceptions", "_UFuncBinaryResolutionError",
        &exc_type);
    if (exc_type == NULL) {
        return -1;
    }

    /* produce an error object */
    exc_value = Py_BuildValue(
        "O(OO)", ufunc,
        (PyObject *)PyArray_DESCR(operands[0]),
        (PyObject *)PyArray_DESCR(operands[1])
    );
    if (exc_value == NULL){
        return -1;
    }
    PyErr_SetObject(exc_type, exc_value);
    Py_DECREF(exc_value);

    return -1;
}