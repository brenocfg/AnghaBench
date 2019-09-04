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
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _find_array_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _get_output_array_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_um_str_array_prepare ; 

__attribute__((used)) static void
_find_array_prepare(ufunc_full_args args,
                    PyObject **output_prep, int nin, int nout)
{
    int i;
    PyObject *prep;

    /*
     * Determine the prepping function given by the input arrays
     * (could be NULL).
     */
    prep = _find_array_method(args.in, npy_um_str_array_prepare);
    /*
     * For all the output arrays decide what to do.
     *
     * 1) Use the prep function determined from the input arrays
     * This is the default if the output array is not
     * passed in.
     *
     * 2) Use the __array_prepare__ method of the output object.
     * This is special cased for
     * exact ndarray so that no PyArray_Return is
     * done in that case.
     */
    if (args.out == NULL) {
        for (i = 0; i < nout; i++) {
            Py_XINCREF(prep);
            output_prep[i] = prep;
        }
    }
    else {
        for (i = 0; i < nout; i++) {
            output_prep[i] = _get_output_array_method(
                PyTuple_GET_ITEM(args.out, i), npy_um_str_array_prepare, prep);
        }
    }
    Py_XDECREF(prep);
    return;
}