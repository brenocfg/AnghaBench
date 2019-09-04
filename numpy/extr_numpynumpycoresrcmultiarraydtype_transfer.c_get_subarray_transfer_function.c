#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_intp ;
struct TYPE_21__ {TYPE_1__* subarray; } ;
struct TYPE_20__ {int member_1; scalar_t__ len; int /*<<< orphan*/  ptr; int /*<<< orphan*/ * member_0; } ;
struct TYPE_19__ {TYPE_3__* base; int /*<<< orphan*/  shape; } ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  TYPE_2__ PyArray_Dims ;
typedef  TYPE_3__ PyArray_Descr ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int NPY_FAIL ; 
 scalar_t__ PyArray_CompareLists (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int PyArray_GetDTypeTransferFunction (int,int,int,TYPE_3__*,TYPE_3__*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  PyArray_IntpConverter (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int PyArray_MultiplyList (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PyDataType_HASSUBARRAY (TYPE_3__*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int get_n_to_n_transfer_function (int,int,int,TYPE_3__*,TYPE_3__*,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*) ; 
 int get_one_to_n_transfer_function (int,int,int,TYPE_3__*,TYPE_3__*,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*) ; 
 int get_subarray_broadcast_transfer_function (int,int,int,TYPE_3__*,TYPE_3__*,int,int,TYPE_2__,TYPE_2__,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  npy_free_cache_dim_obj (TYPE_2__) ; 

__attribute__((used)) static int
get_subarray_transfer_function(int aligned,
                            npy_intp src_stride, npy_intp dst_stride,
                            PyArray_Descr *src_dtype, PyArray_Descr *dst_dtype,
                            int move_references,
                            PyArray_StridedUnaryOp **out_stransfer,
                            NpyAuxData **out_transferdata,
                            int *out_needs_api)
{
    PyArray_Dims src_shape = {NULL, -1}, dst_shape = {NULL, -1};
    npy_intp src_size = 1, dst_size = 1;

    /* Get the subarray shapes and sizes */
    if (PyDataType_HASSUBARRAY(src_dtype)) {
        if (!(PyArray_IntpConverter(src_dtype->subarray->shape,
                                            &src_shape))) {
            PyErr_SetString(PyExc_ValueError,
                    "invalid subarray shape");
            return NPY_FAIL;
        }
        src_size = PyArray_MultiplyList(src_shape.ptr, src_shape.len);
        src_dtype = src_dtype->subarray->base;
    }
    if (PyDataType_HASSUBARRAY(dst_dtype)) {
        if (!(PyArray_IntpConverter(dst_dtype->subarray->shape,
                                            &dst_shape))) {
            npy_free_cache_dim_obj(src_shape);
            PyErr_SetString(PyExc_ValueError,
                    "invalid subarray shape");
            return NPY_FAIL;
        }
        dst_size = PyArray_MultiplyList(dst_shape.ptr, dst_shape.len);
        dst_dtype = dst_dtype->subarray->base;
    }

    /*
     * Just a straight one-element copy.
     */
    if (dst_size == 1 && src_size == 1) {
        npy_free_cache_dim_obj(src_shape);
        npy_free_cache_dim_obj(dst_shape);

        return PyArray_GetDTypeTransferFunction(aligned,
                src_stride, dst_stride,
                src_dtype, dst_dtype,
                move_references,
                out_stransfer, out_transferdata,
                out_needs_api);
    }
    /* Copy the src value to all the dst values */
    else if (src_size == 1) {
        npy_free_cache_dim_obj(src_shape);
        npy_free_cache_dim_obj(dst_shape);

        return get_one_to_n_transfer_function(aligned,
                        src_stride, dst_stride,
                        src_dtype, dst_dtype,
                        move_references,
                        dst_size,
                        out_stransfer, out_transferdata,
                        out_needs_api);
    }
    /* If the shapes match exactly, do an n to n copy */
    else if (src_shape.len == dst_shape.len &&
               PyArray_CompareLists(src_shape.ptr, dst_shape.ptr,
                                                    src_shape.len)) {
        npy_free_cache_dim_obj(src_shape);
        npy_free_cache_dim_obj(dst_shape);

        return get_n_to_n_transfer_function(aligned,
                        src_stride, dst_stride,
                        src_dtype, dst_dtype,
                        move_references,
                        src_size,
                        out_stransfer, out_transferdata,
                        out_needs_api);
    }
    /*
     * Copy the subarray with broadcasting, truncating, and zero-padding
     * as necessary.
     */
    else {
        int ret = get_subarray_broadcast_transfer_function(aligned,
                        src_stride, dst_stride,
                        src_dtype, dst_dtype,
                        src_size, dst_size,
                        src_shape, dst_shape,
                        move_references,
                        out_stransfer, out_transferdata,
                        out_needs_api);

        npy_free_cache_dim_obj(src_shape);
        npy_free_cache_dim_obj(dst_shape);
        return ret;
    }
}