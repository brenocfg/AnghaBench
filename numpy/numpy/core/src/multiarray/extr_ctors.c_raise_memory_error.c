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
typedef  int /*<<< orphan*/  npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/ * PyArray_IntTupleFromIntp (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_WriteUnraisable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_Pack (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_cache_import (char*,char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static PyObject *
raise_memory_error(int nd, npy_intp *dims, PyArray_Descr *descr)
{
    static PyObject *exc_type = NULL;

    npy_cache_import(
        "numpy.core._exceptions", "_ArrayMemoryError",
        &exc_type);
    if (exc_type == NULL) {
        goto fail;
    }

    PyObject *shape = PyArray_IntTupleFromIntp(nd, dims);
    if (shape == NULL) {
        goto fail;
    }

    /* produce an error object */
    PyObject *exc_value = PyTuple_Pack(2, shape, (PyObject *)descr);
    Py_DECREF(shape);
    if (exc_value == NULL){
        goto fail;
    }
    PyErr_SetObject(exc_type, exc_value);
    Py_DECREF(exc_value);
    return NULL;

fail:
    /* we couldn't raise the formatted exception for some reason */
    PyErr_WriteUnraisable(NULL);
    return PyErr_NoMemory();
}