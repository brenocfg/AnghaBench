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
typedef  int /*<<< orphan*/  npyiter_opitflags ;
typedef  int npy_uint32 ;
typedef  int npy_int8 ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_ITER_ARRAYMASK ; 
 int NPY_ITER_WRITEMASKED ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npyiter_check_per_op_flags (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npyiter_prepare_one_operand (int /*<<< orphan*/ **,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
npyiter_prepare_operands(int nop, PyArrayObject **op_in,
                    PyArrayObject **op,
                    char **op_dataptr,
                    PyArray_Descr **op_request_dtypes,
                    PyArray_Descr **op_dtype,
                    npy_uint32 flags,
                    npy_uint32 *op_flags, npyiter_opitflags *op_itflags,
                    npy_int8 *out_maskop)
{
    int iop, i;
    npy_int8 maskop = -1;
    int any_writemasked_ops = 0;

    /*
     * Here we just prepare the provided operands.
     */
    for (iop = 0; iop < nop; ++iop) {
        op[iop] = op_in[iop];
        Py_XINCREF(op[iop]);
        op_dtype[iop] = NULL;

        /* Check the readonly/writeonly flags, and fill in op_itflags */
        if (!npyiter_check_per_op_flags(op_flags[iop], &op_itflags[iop])) {
            goto fail_iop;
        }

        /* Extract the operand which is for masked iteration */
        if ((op_flags[iop] & NPY_ITER_ARRAYMASK) != 0) {
            if (maskop != -1) {
                PyErr_SetString(PyExc_ValueError,
                        "Only one iterator operand may receive an "
                        "ARRAYMASK flag");
                goto fail_iop;
            }

            maskop = iop;
            *out_maskop = iop;
        }

        if (op_flags[iop] & NPY_ITER_WRITEMASKED) {
            any_writemasked_ops = 1;
        }

        /*
         * Prepare the operand.  This produces an op_dtype[iop] reference
         * on success.
         */
        if (!npyiter_prepare_one_operand(&op[iop],
                        &op_dataptr[iop],
                        op_request_dtypes ? op_request_dtypes[iop] : NULL,
                        &op_dtype[iop],
                        flags,
                        op_flags[iop], &op_itflags[iop])) {
            goto fail_iop;
        }
    }

    /* If all the operands were NULL, it's an error */
    if (op[0] == NULL) {
        int all_null = 1;
        for (iop = 1; iop < nop; ++iop) {
            if (op[iop] != NULL) {
                all_null = 0;
                break;
            }
        }
        if (all_null) {
            PyErr_SetString(PyExc_ValueError,
                    "At least one iterator operand must be non-NULL");
            goto fail_nop;
        }
    }

    if (any_writemasked_ops && maskop < 0) {
        PyErr_SetString(PyExc_ValueError,
                "An iterator operand was flagged as WRITEMASKED, "
                "but no ARRAYMASK operand was given to supply "
                "the mask");
        goto fail_nop;
    }
    else if (!any_writemasked_ops && maskop >= 0) {
        PyErr_SetString(PyExc_ValueError,
                "An iterator operand was flagged as the ARRAYMASK, "
                "but no WRITEMASKED operands were given to use "
                "the mask");
        goto fail_nop;
    }

    return 1;

  fail_nop:
    iop = nop - 1;
  fail_iop:
    for (i = 0; i < iop+1; ++i) {
        Py_XDECREF(op[i]);
        Py_XDECREF(op_dtype[i]);
    }
    return 0;
}