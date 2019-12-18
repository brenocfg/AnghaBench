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
 int /*<<< orphan*/  PyArray_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_NewFromDescrAndBase (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PyTuple_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 scalar_t__ Py_TYPE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_preparearray(PyArrayObject *self, PyObject *args)
{
    PyObject *obj;
    PyArrayObject *arr;
    PyArray_Descr *dtype;

    if (PyTuple_Size(args) < 1) {
        PyErr_SetString(PyExc_TypeError,
                        "only accepts 1 argument");
        return NULL;
    }
    obj = PyTuple_GET_ITEM(args, 0);
    if (!PyArray_Check(obj)) {
        PyErr_SetString(PyExc_TypeError,
                        "can only be called with ndarray object");
        return NULL;
    }
    arr = (PyArrayObject *)obj;

    if (Py_TYPE(self) == Py_TYPE(arr)) {
        /* No need to create a new view */
        Py_INCREF(arr);
        return (PyObject *)arr;
    }

    dtype = PyArray_DESCR(arr);
    Py_INCREF(dtype);
    return PyArray_NewFromDescrAndBase(
            Py_TYPE(self), dtype,
            PyArray_NDIM(arr), PyArray_DIMS(arr), PyArray_STRIDES(arr),
            PyArray_DATA(arr),
            PyArray_FLAGS(arr), (PyObject *)self, (PyObject *)arr);
}