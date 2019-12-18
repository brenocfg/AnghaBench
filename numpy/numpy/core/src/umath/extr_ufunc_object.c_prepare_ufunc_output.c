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
typedef  int /*<<< orphan*/  ufunc_full_args ;
typedef  int /*<<< orphan*/  PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_CompareLists (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_EquivTypes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * PyObject_CallFunction (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * _get_wrap_prepare_args (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
prepare_ufunc_output(PyUFuncObject *ufunc,
                    PyArrayObject **op,
                    PyObject *arr_prep,
                    ufunc_full_args full_args,
                    int i)
{
    if (arr_prep != NULL && arr_prep != Py_None) {
        PyObject *res;
        PyArrayObject *arr;
        PyObject *args_tup;

        /* Call with the context argument */
        args_tup = _get_wrap_prepare_args(full_args);
        if (args_tup == NULL) {
            return -1;
        }
        res = PyObject_CallFunction(
            arr_prep, "O(OOi)", *op, ufunc, args_tup, i);
        Py_DECREF(args_tup);

        if (res == NULL) {
            return -1;
        }
        else if (!PyArray_Check(res)) {
            PyErr_SetString(PyExc_TypeError,
                    "__array_prepare__ must return an "
                    "ndarray or subclass thereof");
            Py_DECREF(res);
            return -1;
        }
        arr = (PyArrayObject *)res;

        /* If the same object was returned, nothing to do */
        if (arr == *op) {
            Py_DECREF(arr);
        }
        /* If the result doesn't match, throw an error */
        else if (PyArray_NDIM(arr) != PyArray_NDIM(*op) ||
                !PyArray_CompareLists(PyArray_DIMS(arr),
                                      PyArray_DIMS(*op),
                                      PyArray_NDIM(arr)) ||
                !PyArray_CompareLists(PyArray_STRIDES(arr),
                                      PyArray_STRIDES(*op),
                                      PyArray_NDIM(arr)) ||
                !PyArray_EquivTypes(PyArray_DESCR(arr),
                                    PyArray_DESCR(*op))) {
            PyErr_SetString(PyExc_TypeError,
                    "__array_prepare__ must return an "
                    "ndarray or subclass thereof which is "
                    "otherwise identical to its input");
            Py_DECREF(arr);
            return -1;
        }
        /* Replace the op value */
        else {
            Py_DECREF(*op);
            *op = arr;
        }
    }

    return 0;
}