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
struct TYPE_3__ {int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; } ;
typedef  TYPE_1__ ufunc_full_args ;
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyDict_GetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GetSlice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  npy_um_str_out ; 
 scalar_t__ tuple_all_none (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
make_full_arg_tuple(
        ufunc_full_args *full_args,
        npy_intp nin, npy_intp nout,
        PyObject *args, PyObject *kwds)
{
    PyObject *out_kwd = NULL;
    npy_intp nargs = PyTuple_GET_SIZE(args);
    npy_intp i;

    /* This should have been checked by the caller */
    assert(nin <= nargs && nargs <= nin + nout);

    /* Initialize so we can XDECREF safely */
    full_args->in = NULL;
    full_args->out = NULL;

    /* Get the input arguments*/
    full_args->in = PyTuple_GetSlice(args, 0, nin);
    if (full_args->in == NULL) {
        goto fail;
    }

    /* Look for output keyword arguments */
    out_kwd = kwds ? PyDict_GetItem(kwds, npy_um_str_out) : NULL;

    if (out_kwd != NULL) {
        assert(nargs == nin);
        if (out_kwd == Py_None) {
            return 0;
        }
        else if (PyTuple_Check(out_kwd)) {
            assert(PyTuple_GET_SIZE(out_kwd) == nout);
            if (tuple_all_none(out_kwd)) {
                return 0;
            }
            Py_INCREF(out_kwd);
            full_args->out = out_kwd;
            return 0;
        }
        else {
            /* A single argument x is promoted to (x, None, None ...) */
            full_args->out = PyTuple_New(nout);
            if (full_args->out == NULL) {
                goto fail;
            }
            Py_INCREF(out_kwd);
            PyTuple_SET_ITEM(full_args->out, 0, out_kwd);
            for (i = 1; i < nout; ++i) {
                Py_INCREF(Py_None);
                PyTuple_SET_ITEM(full_args->out, i, Py_None);
            }
            return 0;
        }
    }

    /* No outputs in kwargs; if also none in args, we're done */
    if (nargs == nin) {
        return 0;
    }
    /* copy across positional output arguments, adding trailing Nones */
    full_args->out = PyTuple_New(nout);
    if (full_args->out == NULL) {
        goto fail;
    }
    for (i = nin; i < nargs; ++i) {
        PyObject *item = PyTuple_GET_ITEM(args, i);
        Py_INCREF(item);
        PyTuple_SET_ITEM(full_args->out, i - nin, item);
    }
    for (i = nargs; i < nin + nout; ++i) {
        Py_INCREF(Py_None);
        PyTuple_SET_ITEM(full_args->out, i - nin, Py_None);
    }

    /* don't return a tuple full of None */
    if (tuple_all_none(full_args->out)) {
        Py_DECREF(full_args->out);
        full_args->out = NULL;
    }
    return 0;

fail:
    Py_XDECREF(full_args->in);
    Py_XDECREF(full_args->out);
    return -1;
}