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
typedef  scalar_t__ mem_overlap_t ;
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ MEM_OVERLAP_NO ; 
 scalar_t__ MEM_OVERLAP_OVERFLOW ; 
 scalar_t__ MEM_OVERLAP_TOO_HARD ; 
 scalar_t__ MEM_OVERLAP_YES ; 
 int /*<<< orphan*/  NPY_BEGIN_THREADS ; 
 int /*<<< orphan*/  NPY_BEGIN_THREADS_DEF ; 
 int /*<<< orphan*/  NPY_END_THREADS ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_FROM_O (int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PyExc_OverflowError ; 
 int /*<<< orphan*/ * PyExc_RuntimeError ; 
 int /*<<< orphan*/ * PyExc_ValueError ; 
 int PyInt_AsSsize_t (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_Check (int /*<<< orphan*/ *) ; 
 int PyLong_AsSsize_t (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_RETURN_FALSE ; 
 int /*<<< orphan*/  Py_RETURN_TRUE ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_cache_import (char*,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ solve_may_share_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static PyObject *
array_shares_memory_impl(PyObject *args, PyObject *kwds, Py_ssize_t default_max_work,
                         int raise_exceptions)
{
    PyObject * self_obj = NULL;
    PyObject * other_obj = NULL;
    PyArrayObject * self = NULL;
    PyArrayObject * other = NULL;
    PyObject *max_work_obj = NULL;
    static char *kwlist[] = {"self", "other", "max_work", NULL};

    mem_overlap_t result;
    static PyObject *too_hard_cls = NULL;
    Py_ssize_t max_work;
    NPY_BEGIN_THREADS_DEF;

    max_work = default_max_work;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO|O:shares_memory_impl", kwlist,
                                     &self_obj, &other_obj, &max_work_obj)) {
        return NULL;
    }

    if (PyArray_Check(self_obj)) {
        self = (PyArrayObject*)self_obj;
        Py_INCREF(self);
    }
    else {
        /* Use FromAny to enable checking overlap for objects exposing array
           interfaces etc. */
        self = (PyArrayObject*)PyArray_FROM_O(self_obj);
        if (self == NULL) {
            goto fail;
        }
    }

    if (PyArray_Check(other_obj)) {
        other = (PyArrayObject*)other_obj;
        Py_INCREF(other);
    }
    else {
        other = (PyArrayObject*)PyArray_FROM_O(other_obj);
        if (other == NULL) {
            goto fail;
        }
    }

    if (max_work_obj == NULL || max_work_obj == Py_None) {
        /* noop */
    }
    else if (PyLong_Check(max_work_obj)) {
        max_work = PyLong_AsSsize_t(max_work_obj);
        if (PyErr_Occurred()) {
            goto fail;
        }
    }
#if !defined(NPY_PY3K)
    else if (PyInt_Check(max_work_obj)) {
        max_work = PyInt_AsSsize_t(max_work_obj);
    }
#endif
    else {
        PyErr_SetString(PyExc_ValueError, "max_work must be an integer");
        goto fail;
    }

    if (max_work < -2) {
        PyErr_SetString(PyExc_ValueError, "Invalid value for max_work");
        goto fail;
    }

    NPY_BEGIN_THREADS;
    result = solve_may_share_memory(self, other, max_work);
    NPY_END_THREADS;

    Py_XDECREF(self);
    Py_XDECREF(other);

    if (result == MEM_OVERLAP_NO) {
        Py_RETURN_FALSE;
    }
    else if (result == MEM_OVERLAP_YES) {
        Py_RETURN_TRUE;
    }
    else if (result == MEM_OVERLAP_OVERFLOW) {
        if (raise_exceptions) {
            PyErr_SetString(PyExc_OverflowError,
                            "Integer overflow in computing overlap");
            return NULL;
        }
        else {
            /* Don't know, so say yes */
            Py_RETURN_TRUE;
        }
    }
    else if (result == MEM_OVERLAP_TOO_HARD) {
        if (raise_exceptions) {
            npy_cache_import("numpy.core._exceptions", "TooHardError",
                             &too_hard_cls);
            if (too_hard_cls) {
                PyErr_SetString(too_hard_cls, "Exceeded max_work");
            }
            return NULL;
        }
        else {
            /* Don't know, so say yes */
            Py_RETURN_TRUE;
        }
    }
    else {
        /* Doesn't happen usually */
        PyErr_SetString(PyExc_RuntimeError,
                        "Error in computing overlap");
        return NULL;
    }

fail:
    Py_XDECREF(self);
    Py_XDECREF(other);
    return NULL;
}