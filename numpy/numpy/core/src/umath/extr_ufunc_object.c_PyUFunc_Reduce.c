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
typedef  int npy_bool ;
typedef  int /*<<< orphan*/  PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_MAXDIMS ; 
 int /*<<< orphan*/  NPY_UF_DBG_PRINT1 (char*,char const*) ; 
 int /*<<< orphan*/  NPY_UNSAFE_CASTING ; 
 scalar_t__ PyArray_ISOBJECT (int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyUFunc_ReduceWrapper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*,int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 scalar_t__ _get_bufsize_errmask (int /*<<< orphan*/ *,char*,int*,int*) ; 
 int /*<<< orphan*/ * _get_identity (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  npy_cache_import (char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  reduce_loop ; 
 scalar_t__ reduce_type_resolver (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 char* ufunc_get_name_cstr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyArrayObject *
PyUFunc_Reduce(PyUFuncObject *ufunc, PyArrayObject *arr, PyArrayObject *out,
        int naxes, int *axes, PyArray_Descr *odtype, int keepdims,
        PyObject *initial, PyArrayObject *wheremask)
{
    int iaxes, ndim;
    npy_bool reorderable;
    npy_bool axis_flags[NPY_MAXDIMS];
    PyArray_Descr *dtype;
    PyArrayObject *result;
    PyObject *identity;
    const char *ufunc_name = ufunc_get_name_cstr(ufunc);
    /* These parameters come from a TLS global */
    int buffersize = 0, errormask = 0;
    static PyObject *NoValue = NULL;

    NPY_UF_DBG_PRINT1("\nEvaluating ufunc %s.reduce\n", ufunc_name);

    npy_cache_import("numpy", "_NoValue", &NoValue);
    if (NoValue == NULL) return NULL;

    ndim = PyArray_NDIM(arr);

    /* Create an array of flags for reduction */
    memset(axis_flags, 0, ndim);
    for (iaxes = 0; iaxes < naxes; ++iaxes) {
        int axis = axes[iaxes];
        if (axis_flags[axis]) {
            PyErr_SetString(PyExc_ValueError,
                    "duplicate value in 'axis'");
            return NULL;
        }
        axis_flags[axis] = 1;
    }

    if (_get_bufsize_errmask(NULL, "reduce", &buffersize, &errormask) < 0) {
        return NULL;
    }

    /* Get the identity */
    identity = _get_identity(ufunc, &reorderable);
    if (identity == NULL) {
        return NULL;
    }

    /* Get the initial value */
    if (initial == NULL || initial == NoValue) {
        initial = identity;

        /*
        * The identity for a dynamic dtype like
        * object arrays can't be used in general
        */
        if (initial != Py_None && PyArray_ISOBJECT(arr) && PyArray_SIZE(arr) != 0) {
            Py_DECREF(initial);
            initial = Py_None;
            Py_INCREF(initial);
        }
    } else {
        Py_DECREF(identity);
        Py_INCREF(initial);  /* match the reference count in the if above */
    }

    /* Get the reduction dtype */
    if (reduce_type_resolver(ufunc, arr, odtype, &dtype) < 0) {
        Py_DECREF(initial);
        return NULL;
    }

    result = PyUFunc_ReduceWrapper(arr, out, wheremask, dtype, dtype,
                                   NPY_UNSAFE_CASTING,
                                   axis_flags, reorderable,
                                   keepdims, 0,
                                   initial,
                                   reduce_loop,
                                   ufunc, buffersize, ufunc_name, errormask);

    Py_DECREF(dtype);
    Py_DECREF(initial);
    return result;
}