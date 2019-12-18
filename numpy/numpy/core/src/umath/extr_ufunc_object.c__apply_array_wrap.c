#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  out_i; int /*<<< orphan*/  ufunc; int /*<<< orphan*/  args; } ;
typedef  TYPE_1__ _ufunc_context ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyArray_Return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_ExceptionMatches (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * _get_wrap_prepare_args (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
_apply_array_wrap(
            PyObject *wrap, PyArrayObject *obj, _ufunc_context const *context) {
    if (wrap == NULL) {
        /* default behavior */
        return PyArray_Return(obj);
    }
    else if (wrap == Py_None) {
        Py_DECREF(wrap);
        return (PyObject *)obj;
    }
    else {
        PyObject *res;
        PyObject *py_context = NULL;

        /* Convert the context object to a tuple, if present */
        if (context == NULL) {
            py_context = Py_None;
            Py_INCREF(py_context);
        }
        else {
            PyObject *args_tup;
            /* Call the method with appropriate context */
            args_tup = _get_wrap_prepare_args(context->args);
            if (args_tup == NULL) {
                goto fail;
            }
            py_context = Py_BuildValue("OOi",
                context->ufunc, args_tup, context->out_i);
            Py_DECREF(args_tup);
            if (py_context == NULL) {
                goto fail;
            }
        }
        /* try __array_wrap__(obj, context) */
        res = PyObject_CallFunctionObjArgs(wrap, obj, py_context, NULL);
        Py_DECREF(py_context);

        /* try __array_wrap__(obj) if the context argument is not accepted  */
        if (res == NULL && PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            res = PyObject_CallFunctionObjArgs(wrap, obj, NULL);
        }
        Py_DECREF(wrap);
        Py_DECREF(obj);
        return res;
    fail:
        Py_DECREF(wrap);
        Py_DECREF(obj);
        return NULL;
    }
}