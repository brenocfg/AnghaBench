#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_intp ;
struct TYPE_15__ {int offset; int count; } ;
typedef  TYPE_2__ _subarray_broadcast_offsetrun ;
struct TYPE_14__ {int /*<<< orphan*/ * clone; int /*<<< orphan*/ * free; } ;
struct TYPE_16__ {int src_N; int dst_N; int src_itemsize; int dst_itemsize; int run_count; int /*<<< orphan*/ * stransfer_decdstref; int /*<<< orphan*/ * stransfer_decsrcref; TYPE_2__ offsetruns; int /*<<< orphan*/ * data_decdstref; int /*<<< orphan*/ * data_decsrcref; int /*<<< orphan*/ * data; TYPE_1__ base; int /*<<< orphan*/ * stransfer; } ;
typedef  TYPE_3__ _subarray_broadcast_data ;
struct TYPE_18__ {int elsize; } ;
struct TYPE_17__ {scalar_t__ len; int* ptr; } ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  TYPE_4__ PyArray_Dims ;
typedef  TYPE_5__ PyArray_Descr ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ *) ; 
 int NPY_FAIL ; 
 scalar_t__ NPY_SUCCEED ; 
 scalar_t__ PyArray_GetDTypeTransferFunction (int,int,int,TYPE_5__*,TYPE_5__*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  PyArray_free (TYPE_3__*) ; 
 scalar_t__ PyArray_malloc (int) ; 
 scalar_t__ PyDataType_REFCHK (TYPE_5__*) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  _strided_to_strided_subarray_broadcast ; 
 int /*<<< orphan*/  _strided_to_strided_subarray_broadcast_withrefs ; 
 int /*<<< orphan*/  _subarray_broadcast_data_clone ; 
 int /*<<< orphan*/  _subarray_broadcast_data_free ; 

__attribute__((used)) static int
get_subarray_broadcast_transfer_function(int aligned,
                            npy_intp src_stride, npy_intp dst_stride,
                            PyArray_Descr *src_dtype, PyArray_Descr *dst_dtype,
                            npy_intp src_size, npy_intp dst_size,
                            PyArray_Dims src_shape, PyArray_Dims dst_shape,
                            int move_references,
                            PyArray_StridedUnaryOp **out_stransfer,
                            NpyAuxData **out_transferdata,
                            int *out_needs_api)
{
    _subarray_broadcast_data *data;
    npy_intp structsize, loop_index, run, run_size,
             src_index, dst_index, i, ndim;
    _subarray_broadcast_offsetrun *offsetruns;

    structsize = sizeof(_subarray_broadcast_data) +
                        dst_size*sizeof(_subarray_broadcast_offsetrun);

    /* Allocate the data and populate it */
    data = (_subarray_broadcast_data *)PyArray_malloc(structsize);
    if (data == NULL) {
        PyErr_NoMemory();
        return NPY_FAIL;
    }

    /*
     * move_references is set to 0, handled in the wrapping transfer fn,
     * src_stride and dst_stride are set to contiguous, as N will always
     * be 1 when it's called.
     */
    if (PyArray_GetDTypeTransferFunction(aligned,
                    src_dtype->elsize, dst_dtype->elsize,
                    src_dtype, dst_dtype,
                    0,
                    &data->stransfer, &data->data,
                    out_needs_api) != NPY_SUCCEED) {
        PyArray_free(data);
        return NPY_FAIL;
    }
    data->base.free = &_subarray_broadcast_data_free;
    data->base.clone = &_subarray_broadcast_data_clone;
    data->src_N = src_size;
    data->dst_N = dst_size;
    data->src_itemsize = src_dtype->elsize;
    data->dst_itemsize = dst_dtype->elsize;

    /* If the src object will need a DECREF */
    if (move_references && PyDataType_REFCHK(src_dtype)) {
        if (PyArray_GetDTypeTransferFunction(aligned,
                        src_dtype->elsize, 0,
                        src_dtype, NULL,
                        1,
                        &data->stransfer_decsrcref,
                        &data->data_decsrcref,
                        out_needs_api) != NPY_SUCCEED) {
            NPY_AUXDATA_FREE(data->data);
            PyArray_free(data);
            return NPY_FAIL;
        }
    }
    else {
        data->stransfer_decsrcref = NULL;
        data->data_decsrcref = NULL;
    }

    /* If the dst object needs a DECREF to set it to NULL */
    if (PyDataType_REFCHK(dst_dtype)) {
        if (PyArray_GetDTypeTransferFunction(aligned,
                        dst_dtype->elsize, 0,
                        dst_dtype, NULL,
                        1,
                        &data->stransfer_decdstref,
                        &data->data_decdstref,
                        out_needs_api) != NPY_SUCCEED) {
            NPY_AUXDATA_FREE(data->data);
            NPY_AUXDATA_FREE(data->data_decsrcref);
            PyArray_free(data);
            return NPY_FAIL;
        }
    }
    else {
        data->stransfer_decdstref = NULL;
        data->data_decdstref = NULL;
    }

    /* Calculate the broadcasting and set the offsets */
    offsetruns = &data->offsetruns;
    ndim = (src_shape.len > dst_shape.len) ? src_shape.len : dst_shape.len;
    for (loop_index = 0; loop_index < dst_size; ++loop_index) {
        npy_intp src_factor = 1;

        dst_index = loop_index;
        src_index = 0;
        for (i = ndim-1; i >= 0; --i) {
            npy_intp coord = 0, shape;

            /* Get the dst coord of this index for dimension i */
            if (i >= ndim - dst_shape.len) {
                shape = dst_shape.ptr[i-(ndim-dst_shape.len)];
                coord = dst_index % shape;
                dst_index /= shape;
            }

            /* Translate it into a src coord and update src_index */
            if (i >= ndim - src_shape.len) {
                shape = src_shape.ptr[i-(ndim-src_shape.len)];
                if (shape == 1) {
                    coord = 0;
                }
                else {
                    if (coord < shape) {
                        src_index += src_factor*coord;
                        src_factor *= shape;
                    }
                    else {
                        /* Out of bounds, flag with -1 */
                        src_index = -1;
                        break;
                    }
                }
            }
        }
        /* Set the offset */
        if (src_index == -1) {
            offsetruns[loop_index].offset = -1;
        }
        else {
            offsetruns[loop_index].offset = src_index;
        }
    }

    /* Run-length encode the result */
    run = 0;
    run_size = 1;
    for (loop_index = 1; loop_index < dst_size; ++loop_index) {
        if (offsetruns[run].offset == -1) {
            /* Stop the run when there's a valid index again */
            if (offsetruns[loop_index].offset != -1) {
                offsetruns[run].count = run_size;
                run++;
                run_size = 1;
                offsetruns[run].offset = offsetruns[loop_index].offset;
            }
            else {
                run_size++;
            }
        }
        else {
            /* Stop the run when there's a valid index again */
            if (offsetruns[loop_index].offset !=
                            offsetruns[loop_index-1].offset + 1) {
                offsetruns[run].count = run_size;
                run++;
                run_size = 1;
                offsetruns[run].offset = offsetruns[loop_index].offset;
            }
            else {
                run_size++;
            }
        }
    }
    offsetruns[run].count = run_size;
    run++;
    data->run_count = run;

    /* Multiply all the offsets by the src item size */
    while (run--) {
        if (offsetruns[run].offset != -1) {
            offsetruns[run].offset *= src_dtype->elsize;
        }
    }

    if (data->stransfer_decsrcref == NULL &&
                                data->stransfer_decdstref == NULL) {
        *out_stransfer = &_strided_to_strided_subarray_broadcast;
    }
    else {
        *out_stransfer = &_strided_to_strided_subarray_broadcast_withrefs;
    }
    *out_transferdata = (NpyAuxData *)data;

    return NPY_SUCCEED;
}