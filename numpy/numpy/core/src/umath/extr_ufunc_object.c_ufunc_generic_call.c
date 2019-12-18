#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ ufunc_full_args ;
struct TYPE_11__ {int out_i; TYPE_1__ args; TYPE_3__* ufunc; } ;
typedef  TYPE_2__ _ufunc_context ;
struct TYPE_12__ {int nin; int nout; int nargs; } ;
typedef  TYPE_3__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyTupleObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_MAXARGS ; 
 scalar_t__ PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int PyUFunc_CheckOverride (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int PyUFunc_GenericFunction (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _apply_array_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  _find_array_wrap (TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int) ; 
 scalar_t__ make_full_arg_tuple (TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
ufunc_generic_call(PyUFuncObject *ufunc, PyObject *args, PyObject *kwds)
{
    int i;
    PyArrayObject *mps[NPY_MAXARGS];
    PyObject *retobj[NPY_MAXARGS];
    PyObject *wraparr[NPY_MAXARGS];
    PyObject *override = NULL;
    ufunc_full_args full_args = {NULL, NULL};
    int errval;

    errval = PyUFunc_CheckOverride(ufunc, "__call__", args, kwds, &override);
    if (errval) {
        return NULL;
    }
    else if (override) {
        return override;
    }

    errval = PyUFunc_GenericFunction(ufunc, args, kwds, mps);
    if (errval < 0) {
        return NULL;
    }

    /* Free the input references */
    for (i = 0; i < ufunc->nin; i++) {
        Py_XDECREF(mps[i]);
    }

    /*
     * Use __array_wrap__ on all outputs
     * if present on one of the input arguments.
     * If present for multiple inputs:
     * use __array_wrap__ of input object with largest
     * __array_priority__ (default = 0.0)
     *
     * Exception:  we should not wrap outputs for items already
     * passed in as output-arguments.  These items should either
     * be left unwrapped or wrapped by calling their own __array_wrap__
     * routine.
     *
     * For each output argument, wrap will be either
     * NULL --- call PyArray_Return() -- default if no output arguments given
     * None --- array-object passed in don't call PyArray_Return
     * method --- the __array_wrap__ method to call.
     */
    if (make_full_arg_tuple(&full_args, ufunc->nin, ufunc->nout, args, kwds) < 0) {
        goto fail;
    }
    _find_array_wrap(full_args, kwds, wraparr, ufunc->nin, ufunc->nout);

    /* wrap outputs */
    for (i = 0; i < ufunc->nout; i++) {
        int j = ufunc->nin+i;
        _ufunc_context context;
        PyObject *wrapped;

        context.ufunc = ufunc;
        context.args = full_args;
        context.out_i = i;

        wrapped = _apply_array_wrap(wraparr[i], mps[j], &context);
        mps[j] = NULL;  /* Prevent fail double-freeing this */
        if (wrapped == NULL) {
            for (j = 0; j < i; j++) {
                Py_DECREF(retobj[j]);
            }
            goto fail;
        }

        retobj[i] = wrapped;
    }

    Py_XDECREF(full_args.in);
    Py_XDECREF(full_args.out);

    if (ufunc->nout == 1) {
        return retobj[0];
    }
    else {
        PyTupleObject *ret;

        ret = (PyTupleObject *)PyTuple_New(ufunc->nout);
        for (i = 0; i < ufunc->nout; i++) {
            PyTuple_SET_ITEM(ret, i, retobj[i]);
        }
        return (PyObject *)ret;
    }

fail:
    Py_XDECREF(full_args.in);
    Py_XDECREF(full_args.out);
    for (i = ufunc->nin; i < ufunc->nargs; i++) {
        Py_XDECREF(mps[i]);
    }
    return NULL;
}