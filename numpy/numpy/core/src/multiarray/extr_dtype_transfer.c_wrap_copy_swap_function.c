#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_intp ;
struct TYPE_9__ {int /*<<< orphan*/ * clone; int /*<<< orphan*/ * free; } ;
struct TYPE_11__ {int swap; int /*<<< orphan*/ * arr; int /*<<< orphan*/  copyswapn; TYPE_1__ base; } ;
typedef  TYPE_3__ _wrap_copy_swap_data ;
struct TYPE_12__ {TYPE_2__* f; } ;
struct TYPE_10__ {int /*<<< orphan*/  copyswapn; } ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  TYPE_4__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int NPY_FAIL ; 
 int NPY_SUCCEED ; 
 scalar_t__ PyArray_NewFromDescr_int (int /*<<< orphan*/ *,TYPE_4__*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/  PyArray_free (TYPE_3__*) ; 
 scalar_t__ PyArray_malloc (int) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_4__*) ; 
 int /*<<< orphan*/  _strided_to_strided_wrap_copy_swap ; 
 int /*<<< orphan*/  _wrap_copy_swap_data_clone ; 
 int /*<<< orphan*/  _wrap_copy_swap_data_free ; 

__attribute__((used)) static int
wrap_copy_swap_function(int aligned,
                npy_intp src_stride, npy_intp dst_stride,
                PyArray_Descr *dtype,
                int should_swap,
                PyArray_StridedUnaryOp **out_stransfer,
                NpyAuxData **out_transferdata)
{
    _wrap_copy_swap_data *data;
    npy_intp shape = 1;

    /* Allocate the data for the copy swap */
    data = (_wrap_copy_swap_data *)PyArray_malloc(sizeof(_wrap_copy_swap_data));
    if (data == NULL) {
        PyErr_NoMemory();
        *out_stransfer = NULL;
        *out_transferdata = NULL;
        return NPY_FAIL;
    }

    data->base.free = &_wrap_copy_swap_data_free;
    data->base.clone = &_wrap_copy_swap_data_clone;
    data->copyswapn = dtype->f->copyswapn;
    data->swap = should_swap;

    /*
     * TODO: This is a hack so the copyswap functions have an array.
     *       The copyswap functions shouldn't need that.
     */
    Py_INCREF(dtype);
    data->arr = (PyArrayObject *)PyArray_NewFromDescr_int(
            &PyArray_Type, dtype,
            1, &shape, NULL, NULL,
            0, NULL, NULL,
            0, 1);
    if (data->arr == NULL) {
        PyArray_free(data);
        return NPY_FAIL;
    }

    *out_stransfer = &_strided_to_strided_wrap_copy_swap;
    *out_transferdata = (NpyAuxData *)data;

    return NPY_SUCCEED;
}