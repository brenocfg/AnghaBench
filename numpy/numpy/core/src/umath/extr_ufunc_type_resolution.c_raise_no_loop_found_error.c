#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t npy_intp ;
struct TYPE_4__ {size_t nargs; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_New (size_t) ; 
 int /*<<< orphan*/ * PyTuple_Pack (int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_cache_import (char*,char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
raise_no_loop_found_error(
        PyUFuncObject *ufunc, PyArray_Descr **dtypes)
{
    static PyObject *exc_type = NULL;
    PyObject *exc_value;
    PyObject *dtypes_tup;
    npy_intp i;

    npy_cache_import(
        "numpy.core._exceptions", "_UFuncNoLoopError",
        &exc_type);
    if (exc_type == NULL) {
        return -1;
    }

    /* convert dtypes to a tuple */
    dtypes_tup = PyTuple_New(ufunc->nargs);
    if (dtypes_tup == NULL) {
        return -1;
    }
    for (i = 0; i < ufunc->nargs; ++i) {
        Py_INCREF(dtypes[i]);
        PyTuple_SET_ITEM(dtypes_tup, i, (PyObject *)dtypes[i]);
    }

    /* produce an error object */
    exc_value = PyTuple_Pack(2, ufunc, dtypes_tup);
    Py_DECREF(dtypes_tup);
    if (exc_value == NULL){
        return -1;
    }
    PyErr_SetObject(exc_type, exc_value);
    Py_DECREF(exc_value);

    return -1;
}