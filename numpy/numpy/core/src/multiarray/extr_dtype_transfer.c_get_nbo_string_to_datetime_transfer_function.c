#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  npy_intp ;
struct TYPE_8__ {int /*<<< orphan*/ * clone; int /*<<< orphan*/ * free; } ;
struct TYPE_9__ {int src_itemsize; int /*<<< orphan*/  dst_meta; int /*<<< orphan*/ * tmp_buffer; TYPE_1__ base; } ;
typedef  TYPE_2__ _strided_datetime_cast_data ;
struct TYPE_10__ {int elsize; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  TYPE_3__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArray_DatetimeMetaData ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int NPY_FAIL ; 
 int NPY_SUCCEED ; 
 int /*<<< orphan*/  PyArray_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * PyArray_malloc (int) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  _safe_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _strided_datetime_cast_data_clone ; 
 int /*<<< orphan*/  _strided_datetime_cast_data_free ; 
 int /*<<< orphan*/  _strided_to_strided_string_to_datetime ; 
 int /*<<< orphan*/ * get_datetime_metadata_from_dtype (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
get_nbo_string_to_datetime_transfer_function(int aligned,
                            npy_intp src_stride, npy_intp dst_stride,
                            PyArray_Descr *src_dtype, PyArray_Descr *dst_dtype,
                            PyArray_StridedUnaryOp **out_stransfer,
                            NpyAuxData **out_transferdata)
{
    PyArray_DatetimeMetaData *dst_meta;
    _strided_datetime_cast_data *data;

    dst_meta = get_datetime_metadata_from_dtype(dst_dtype);
    if (dst_meta == NULL) {
        return NPY_FAIL;
    }

    /* Allocate the data for the casting */
    data = (_strided_datetime_cast_data *)PyArray_malloc(
                                    sizeof(_strided_datetime_cast_data));
    if (data == NULL) {
        PyErr_NoMemory();
        *out_stransfer = NULL;
        *out_transferdata = NULL;
        return NPY_FAIL;
    }
    data->base.free = &_strided_datetime_cast_data_free;
    data->base.clone = &_strided_datetime_cast_data_clone;
    data->src_itemsize = src_dtype->elsize;
    data->tmp_buffer = PyArray_malloc(data->src_itemsize + 1);
    if (data->tmp_buffer == NULL) {
        PyErr_NoMemory();
        PyArray_free(data);
        *out_stransfer = NULL;
        *out_transferdata = NULL;
        return NPY_FAIL;
    }

    memcpy(&data->dst_meta, dst_meta, sizeof(data->dst_meta));

    *out_stransfer = &_strided_to_strided_string_to_datetime;
    *out_transferdata = (NpyAuxData *)data;

#if NPY_DT_DBG_TRACING
    printf("Dtype transfer from ");
    _safe_print((PyObject *)src_dtype);
    printf(" to ");
    _safe_print((PyObject *)dst_dtype);
    printf("\n");
#endif

    return NPY_SUCCEED;
}