#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  npy_intp ;
struct TYPE_15__ {int /*<<< orphan*/  elsize; } ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ *) ; 
 int NPY_FAIL ; 
 int /*<<< orphan*/  NPY_NEEDS_INIT ; 
 int /*<<< orphan*/  NPY_STRING ; 
 scalar_t__ NPY_SUCCEED ; 
 TYPE_1__* PyArray_AdaptFlexibleDType (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_GetDTypeCopySwapFn (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ PyArray_GetDTypeTransferFunction (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  PyDataType_FLAGCHK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 scalar_t__ get_nbo_datetime_to_string_transfer_function (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ wrap_aligned_contig_transfer_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
get_datetime_to_unicode_transfer_function(int aligned,
                            npy_intp src_stride, npy_intp dst_stride,
                            PyArray_Descr *src_dtype, PyArray_Descr *dst_dtype,
                            PyArray_StridedUnaryOp **out_stransfer,
                            NpyAuxData **out_transferdata,
                            int *out_needs_api)
{
    NpyAuxData *castdata = NULL, *todata = NULL, *fromdata = NULL;
    PyArray_StridedUnaryOp *caststransfer, *tobuffer, *frombuffer;
    PyArray_Descr *str_dtype;

    /* Get an ASCII string data type, adapted to match the UNICODE one */
    str_dtype = PyArray_DescrFromType(NPY_STRING);
    str_dtype = PyArray_AdaptFlexibleDType(NULL, dst_dtype, str_dtype);
    if (str_dtype == NULL) {
        return NPY_FAIL;
    }

    /* Get the copy/swap operation to dst */
    if (PyArray_GetDTypeCopySwapFn(aligned,
                            src_stride, src_dtype->elsize,
                            src_dtype,
                            &tobuffer, &todata) != NPY_SUCCEED) {
        Py_DECREF(str_dtype);
        return NPY_FAIL;
    }

    /* Get the NBO datetime to string aligned contig function */
    if (get_nbo_datetime_to_string_transfer_function(1,
                            src_dtype->elsize, str_dtype->elsize,
                            src_dtype, str_dtype,
                            &caststransfer, &castdata) != NPY_SUCCEED) {
        Py_DECREF(str_dtype);
        NPY_AUXDATA_FREE(todata);
        return NPY_FAIL;
    }

    /* Get the cast operation to dst */
    if (PyArray_GetDTypeTransferFunction(aligned,
                            str_dtype->elsize, dst_stride,
                            str_dtype, dst_dtype,
                            0,
                            &frombuffer, &fromdata,
                            out_needs_api) != NPY_SUCCEED) {
        Py_DECREF(str_dtype);
        NPY_AUXDATA_FREE(todata);
        NPY_AUXDATA_FREE(castdata);
        return NPY_FAIL;
    }

    /* Wrap it all up in a new transfer function + data */
    if (wrap_aligned_contig_transfer_function(
                        src_dtype->elsize, str_dtype->elsize,
                        tobuffer, todata,
                        frombuffer, fromdata,
                        caststransfer, castdata,
                        PyDataType_FLAGCHK(str_dtype, NPY_NEEDS_INIT),
                        out_stransfer, out_transferdata) != NPY_SUCCEED) {
        NPY_AUXDATA_FREE(castdata);
        NPY_AUXDATA_FREE(todata);
        NPY_AUXDATA_FREE(fromdata);
        return NPY_FAIL;
    }

    Py_DECREF(str_dtype);

    return NPY_SUCCEED;
}