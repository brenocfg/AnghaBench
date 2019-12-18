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
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SEQUENCE_ERR_MSG ; 
 int /*<<< orphan*/  NON_INTEGRAL_ERROR_MSG ; 
 int /*<<< orphan*/  NPY_MAXDIMS ; 
 int /*<<< orphan*/  PyArray_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_DTypeFromObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PyArray_FromAny (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISBOOL (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISINTEGER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 scalar_t__ PySequence_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySequence_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyArrayObject *
astype_anyint(PyObject *obj) {
    PyArrayObject *ret;

    if (!PyArray_Check(obj)) {
        /* prefer int dtype */
        PyArray_Descr *dtype_guess = NULL;
        if (PyArray_DTypeFromObject(obj, NPY_MAXDIMS, &dtype_guess) < 0) {
            return NULL;
        }
        if (dtype_guess == NULL) {
            if (PySequence_Check(obj) && PySequence_Size(obj) == 0) {
                PyErr_SetString(PyExc_TypeError, EMPTY_SEQUENCE_ERR_MSG);
            }
            return NULL;
        }
        ret = (PyArrayObject*)PyArray_FromAny(obj, dtype_guess, 0, 0, 0, NULL);
        if (ret == NULL) {
            return NULL;
        }
    }
    else {
        ret = (PyArrayObject *)obj;
        Py_INCREF(ret);
    }

    if (!(PyArray_ISINTEGER(ret) || PyArray_ISBOOL(ret))) {
        /* ensure dtype is int-based */
        PyErr_SetString(PyExc_TypeError, NON_INTEGRAL_ERROR_MSG);
        Py_DECREF(ret);
        return NULL;
    }

    return ret;
}