#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* npy_intp ;
struct TYPE_4__ {int /*<<< orphan*/ * clone; int /*<<< orphan*/ * free; } ;
struct TYPE_5__ {void* dst_itemsize; void* N; int /*<<< orphan*/ * data_finish_src; int /*<<< orphan*/ * stransfer_finish_src; int /*<<< orphan*/ * data; int /*<<< orphan*/ * stransfer; TYPE_1__ base; } ;
typedef  TYPE_2__ _one_to_n_data ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int NPY_FAIL ; 
 int NPY_SUCCEED ; 
 TYPE_2__* PyArray_malloc (int) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  _one_to_n_data_clone ; 
 int /*<<< orphan*/  _one_to_n_data_free ; 
 int /*<<< orphan*/  _strided_to_strided_one_to_n ; 
 int /*<<< orphan*/  _strided_to_strided_one_to_n_with_finish ; 

__attribute__((used)) static int
wrap_transfer_function_one_to_n(
                            PyArray_StridedUnaryOp *stransfer_inner,
                            NpyAuxData *data_inner,
                            PyArray_StridedUnaryOp *stransfer_finish_src,
                            NpyAuxData *data_finish_src,
                            npy_intp dst_itemsize,
                            npy_intp N,
                            PyArray_StridedUnaryOp **out_stransfer,
                            NpyAuxData **out_transferdata)
{
    _one_to_n_data *data;


    data = PyArray_malloc(sizeof(_one_to_n_data));
    if (data == NULL) {
        PyErr_NoMemory();
        return NPY_FAIL;
    }

    data->base.free = &_one_to_n_data_free;
    data->base.clone = &_one_to_n_data_clone;
    data->stransfer = stransfer_inner;
    data->data = data_inner;
    data->stransfer_finish_src = stransfer_finish_src;
    data->data_finish_src = data_finish_src;
    data->N = N;
    data->dst_itemsize = dst_itemsize;

    if (stransfer_finish_src == NULL) {
        *out_stransfer = &_strided_to_strided_one_to_n;
    }
    else {
        *out_stransfer = &_strided_to_strided_one_to_n_with_finish;
    }
    *out_transferdata = (NpyAuxData *)data;

    return NPY_SUCCEED;
}