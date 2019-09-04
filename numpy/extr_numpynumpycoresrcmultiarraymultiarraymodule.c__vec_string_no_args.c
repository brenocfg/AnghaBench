#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  ao; int /*<<< orphan*/  dataptr; } ;
typedef  TYPE_1__ PyObject ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  TYPE_1__ PyArrayObject ;
typedef  TYPE_1__ PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_DIMS (TYPE_1__*) ; 
 int /*<<< orphan*/  PyArray_ITER_DATA (TYPE_1__*) ; 
 int /*<<< orphan*/  PyArray_ITER_NEXT (TYPE_1__*) ; 
 scalar_t__ PyArray_ITER_NOTDONE (TYPE_1__*) ; 
 scalar_t__ PyArray_IterNew (TYPE_1__*) ; 
 int /*<<< orphan*/  PyArray_NDIM (TYPE_1__*) ; 
 scalar_t__ PyArray_SETITEM (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ PyArray_SimpleNewFromDescr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* PyArray_ToScalar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 TYPE_1__* PyObject_CallFunctionObjArgs (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XDECREF (TYPE_1__*) ; 

__attribute__((used)) static PyObject *
_vec_string_no_args(PyArrayObject* char_array,
                                   PyArray_Descr* type, PyObject* method)
{
    /*
     * This is a faster version of _vec_string_args to use when there
     * are no additional arguments to the string method.  This doesn't
     * require a broadcast iterator (and broadcast iterators don't work
     * with 1 argument anyway).
     */
    PyArrayIterObject* in_iter = NULL;
    PyArrayObject* result = NULL;
    PyArrayIterObject* out_iter = NULL;

    in_iter = (PyArrayIterObject*)PyArray_IterNew((PyObject*)char_array);
    if (in_iter == NULL) {
        Py_DECREF(type);
        goto err;
    }

    result = (PyArrayObject*)PyArray_SimpleNewFromDescr(
            PyArray_NDIM(char_array), PyArray_DIMS(char_array), type);
    if (result == NULL) {
        goto err;
    }

    out_iter = (PyArrayIterObject*)PyArray_IterNew((PyObject*)result);
    if (out_iter == NULL) {
        goto err;
    }

    while (PyArray_ITER_NOTDONE(in_iter)) {
        PyObject* item_result;
        PyObject* item = PyArray_ToScalar(in_iter->dataptr, in_iter->ao);
        if (item == NULL) {
            goto err;
        }

        item_result = PyObject_CallFunctionObjArgs(method, item, NULL);
        Py_DECREF(item);
        if (item_result == NULL) {
            goto err;
        }

        if (PyArray_SETITEM(result, PyArray_ITER_DATA(out_iter), item_result)) {
            Py_DECREF(item_result);
            PyErr_SetString( PyExc_TypeError,
                "result array type does not match underlying function");
            goto err;
        }
        Py_DECREF(item_result);

        PyArray_ITER_NEXT(in_iter);
        PyArray_ITER_NEXT(out_iter);
    }

    Py_DECREF(in_iter);
    Py_DECREF(out_iter);

    return (PyObject*)result;

 err:
    Py_XDECREF(in_iter);
    Py_XDECREF(out_iter);
    Py_XDECREF(result);

    return 0;
}