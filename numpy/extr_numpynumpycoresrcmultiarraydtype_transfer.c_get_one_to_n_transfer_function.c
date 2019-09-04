#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  npy_intp ;
struct TYPE_8__ {int /*<<< orphan*/  elsize; } ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ *) ; 
 int NPY_FAIL ; 
 scalar_t__ NPY_SUCCEED ; 
 scalar_t__ PyArray_GetDTypeTransferFunction (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ PyDataType_REFCHK (TYPE_1__*) ; 
 scalar_t__ get_decsrcref_transfer_function (int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ wrap_transfer_function_one_to_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
get_one_to_n_transfer_function(int aligned,
                            npy_intp src_stride, npy_intp dst_stride,
                            PyArray_Descr *src_dtype, PyArray_Descr *dst_dtype,
                            int move_references,
                            npy_intp N,
                            PyArray_StridedUnaryOp **out_stransfer,
                            NpyAuxData **out_transferdata,
                            int *out_needs_api)
{
    PyArray_StridedUnaryOp *stransfer, *stransfer_finish_src = NULL;
    NpyAuxData *data, *data_finish_src = NULL;

    /*
     * move_references is set to 0, handled in the wrapping transfer fn,
     * src_stride is set to zero, because its 1 to N copying,
     * and dst_stride is set to contiguous, because subarrays are always
     * contiguous.
     */
    if (PyArray_GetDTypeTransferFunction(aligned,
                    0, dst_dtype->elsize,
                    src_dtype, dst_dtype,
                    0,
                    &stransfer, &data,
                    out_needs_api) != NPY_SUCCEED) {
        return NPY_FAIL;
    }

    /* If the src object will need a DECREF, set src_dtype */
    if (move_references && PyDataType_REFCHK(src_dtype)) {
        if (get_decsrcref_transfer_function(aligned,
                            src_stride,
                            src_dtype,
                            &stransfer_finish_src,
                            &data_finish_src,
                            out_needs_api) != NPY_SUCCEED) {
            NPY_AUXDATA_FREE(data);
            return NPY_FAIL;
        }
    }

    if (wrap_transfer_function_one_to_n(stransfer, data,
                            stransfer_finish_src, data_finish_src,
                            dst_dtype->elsize,
                            N,
                            out_stransfer, out_transferdata) != NPY_SUCCEED) {
        NPY_AUXDATA_FREE(data);
        NPY_AUXDATA_FREE(data_finish_src);
        return NPY_FAIL;
    }

    return NPY_SUCCEED;
}