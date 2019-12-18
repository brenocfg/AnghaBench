#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  npy_longlong ;
struct TYPE_5__ {int nin; scalar_t__ core_enabled; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_NOTYPE ; 
 scalar_t__* PyArray_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_FROM_O (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_FromObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_Reshape (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyInt_FromLong (long) ; 
 int /*<<< orphan*/  PyLong_FromLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyNumber_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyObject_IsInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,int) ; 
 int PySequence_Length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int PyUFunc_CheckOverride (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_cache_import (char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * ufunc_generic_call (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
ufunc_outer(PyUFuncObject *ufunc, PyObject *args, PyObject *kwds)
{
    int i;
    int errval;
    PyObject *override = NULL;
    PyObject *ret;
    PyArrayObject *ap1 = NULL, *ap2 = NULL, *ap_new = NULL;
    PyObject *new_args, *tmp;
    PyObject *shape1, *shape2, *newshape;
    static PyObject *_numpy_matrix;


    errval = PyUFunc_CheckOverride(ufunc, "outer", args, kwds, &override);
    if (errval) {
        return NULL;
    }
    else if (override) {
        return override;
    }

    if (ufunc->core_enabled) {
        PyErr_Format(PyExc_TypeError,
                     "method outer is not allowed in ufunc with non-trivial"\
                     " signature");
        return NULL;
    }

    if (ufunc->nin != 2) {
        PyErr_SetString(PyExc_ValueError,
                        "outer product only supported "\
                        "for binary functions");
        return NULL;
    }

    if (PySequence_Length(args) != 2) {
        PyErr_SetString(PyExc_TypeError, "exactly two arguments expected");
        return NULL;
    }

    tmp = PySequence_GetItem(args, 0);
    if (tmp == NULL) {
        return NULL;
    }

    npy_cache_import(
        "numpy",
        "matrix",
        &_numpy_matrix);

    if (PyObject_IsInstance(tmp, _numpy_matrix)) {
        ap1 = (PyArrayObject *) PyArray_FromObject(tmp, NPY_NOTYPE, 0, 0);
    }
    else {
        ap1 = (PyArrayObject *) PyArray_FROM_O(tmp);
    }
    Py_DECREF(tmp);
    if (ap1 == NULL) {
        return NULL;
    }
    tmp = PySequence_GetItem(args, 1);
    if (tmp == NULL) {
        return NULL;
    }
    if (PyObject_IsInstance(tmp, _numpy_matrix)) {
        ap2 = (PyArrayObject *) PyArray_FromObject(tmp, NPY_NOTYPE, 0, 0);
    }
    else {
        ap2 = (PyArrayObject *) PyArray_FROM_O(tmp);
    }
    Py_DECREF(tmp);
    if (ap2 == NULL) {
        Py_DECREF(ap1);
        return NULL;
    }
    /* Construct new shape tuple */
    shape1 = PyTuple_New(PyArray_NDIM(ap1));
    if (shape1 == NULL) {
        goto fail;
    }
    for (i = 0; i < PyArray_NDIM(ap1); i++) {
        PyTuple_SET_ITEM(shape1, i,
                PyLong_FromLongLong((npy_longlong)PyArray_DIMS(ap1)[i]));
    }
    shape2 = PyTuple_New(PyArray_NDIM(ap2));
    for (i = 0; i < PyArray_NDIM(ap2); i++) {
        PyTuple_SET_ITEM(shape2, i, PyInt_FromLong((long) 1));
    }
    if (shape2 == NULL) {
        Py_DECREF(shape1);
        goto fail;
    }
    newshape = PyNumber_Add(shape1, shape2);
    Py_DECREF(shape1);
    Py_DECREF(shape2);
    if (newshape == NULL) {
        goto fail;
    }
    ap_new = (PyArrayObject *)PyArray_Reshape(ap1, newshape);
    Py_DECREF(newshape);
    if (ap_new == NULL) {
        goto fail;
    }
    new_args = Py_BuildValue("(OO)", ap_new, ap2);
    Py_DECREF(ap1);
    Py_DECREF(ap2);
    Py_DECREF(ap_new);
    ret = ufunc_generic_call(ufunc, new_args, kwds);
    Py_DECREF(new_args);
    return ret;

 fail:
    Py_XDECREF(ap1);
    Py_XDECREF(ap2);
    Py_XDECREF(ap_new);
    return NULL;
}