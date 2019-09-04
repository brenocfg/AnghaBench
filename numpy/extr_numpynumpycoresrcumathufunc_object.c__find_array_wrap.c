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
struct TYPE_3__ {int /*<<< orphan*/ * out; int /*<<< orphan*/  in; } ;
typedef  TYPE_1__ ufunc_full_args ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyDict_GetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * Py_True ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _find_array_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _get_output_array_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_um_str_array_wrap ; 
 int /*<<< orphan*/  npy_um_str_subok ; 

__attribute__((used)) static void
_find_array_wrap(ufunc_full_args args, PyObject *kwds,
                PyObject **output_wrap, int nin, int nout)
{
    int i;
    PyObject *obj;
    PyObject *wrap = NULL;

    /*
     * If a 'subok' parameter is passed and isn't True, don't wrap but put None
     * into slots with out arguments which means return the out argument
     */
    if (kwds != NULL && (obj = PyDict_GetItem(kwds,
                                              npy_um_str_subok)) != NULL) {
        if (obj != Py_True) {
            /* skip search for wrap members */
            goto handle_out;
        }
    }

    /*
     * Determine the wrapping function given by the input arrays
     * (could be NULL).
     */
    wrap = _find_array_method(args.in, npy_um_str_array_wrap);

    /*
     * For all the output arrays decide what to do.
     *
     * 1) Use the wrap function determined from the input arrays
     * This is the default if the output array is not
     * passed in.
     *
     * 2) Use the __array_wrap__ method of the output object
     * passed in. -- this is special cased for
     * exact ndarray so that no PyArray_Return is
     * done in that case.
     */
handle_out:
    if (args.out == NULL) {
        for (i = 0; i < nout; i++) {
            Py_XINCREF(wrap);
            output_wrap[i] = wrap;
        }
    }
    else {
        for (i = 0; i < nout; i++) {
            output_wrap[i] = _get_output_array_method(
                PyTuple_GET_ITEM(args.out, i), npy_um_str_array_wrap, wrap);
        }
    }

    Py_XDECREF(wrap);
    return;
}