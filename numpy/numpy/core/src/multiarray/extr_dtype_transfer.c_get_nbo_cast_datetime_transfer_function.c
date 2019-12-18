#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  npy_intp ;
typedef  scalar_t__ npy_int64 ;
struct TYPE_12__ {int /*<<< orphan*/ * clone; int /*<<< orphan*/ * free; } ;
struct TYPE_13__ {int /*<<< orphan*/  dst_meta; int /*<<< orphan*/  src_meta; int /*<<< orphan*/ * tmp_buffer; scalar_t__ denom; scalar_t__ num; TYPE_1__ base; } ;
typedef  TYPE_2__ _strided_datetime_cast_data ;
struct TYPE_15__ {scalar_t__ base; } ;
struct TYPE_14__ {scalar_t__ type_num; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  TYPE_3__ PyArray_Descr ;
typedef  TYPE_4__ PyArray_DatetimeMetaData ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 scalar_t__ NPY_DATETIME ; 
 int NPY_FAIL ; 
 scalar_t__ NPY_FR_M ; 
 scalar_t__ NPY_FR_Y ; 
 int NPY_SUCCEED ; 
 scalar_t__ PyArray_malloc (int) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  _aligned_strided_to_strided_datetime_cast ; 
 int /*<<< orphan*/  _safe_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _strided_datetime_cast_data_clone ; 
 int /*<<< orphan*/  _strided_datetime_cast_data_free ; 
 int /*<<< orphan*/  _strided_to_strided_datetime_cast ; 
 int /*<<< orphan*/  _strided_to_strided_datetime_general_cast ; 
 int /*<<< orphan*/  get_datetime_conversion_factor (TYPE_4__*,TYPE_4__*,scalar_t__*,scalar_t__*) ; 
 TYPE_4__* get_datetime_metadata_from_dtype (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
get_nbo_cast_datetime_transfer_function(int aligned,
                            npy_intp src_stride, npy_intp dst_stride,
                            PyArray_Descr *src_dtype, PyArray_Descr *dst_dtype,
                            PyArray_StridedUnaryOp **out_stransfer,
                            NpyAuxData **out_transferdata)
{
    PyArray_DatetimeMetaData *src_meta, *dst_meta;
    npy_int64 num = 0, denom = 0;
    _strided_datetime_cast_data *data;

    src_meta = get_datetime_metadata_from_dtype(src_dtype);
    if (src_meta == NULL) {
        return NPY_FAIL;
    }
    dst_meta = get_datetime_metadata_from_dtype(dst_dtype);
    if (dst_meta == NULL) {
        return NPY_FAIL;
    }

    get_datetime_conversion_factor(src_meta, dst_meta, &num, &denom);

    if (num == 0) {
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
    data->num = num;
    data->denom = denom;
    data->tmp_buffer = NULL;

    /*
     * Special case the datetime (but not timedelta) with the nonlinear
     * units (years and months). For timedelta, an average
     * years and months value is used.
     */
    if (src_dtype->type_num == NPY_DATETIME &&
            (src_meta->base == NPY_FR_Y ||
             src_meta->base == NPY_FR_M ||
             dst_meta->base == NPY_FR_Y ||
             dst_meta->base == NPY_FR_M)) {
        memcpy(&data->src_meta, src_meta, sizeof(data->src_meta));
        memcpy(&data->dst_meta, dst_meta, sizeof(data->dst_meta));
        *out_stransfer = &_strided_to_strided_datetime_general_cast;
    }
    else if (aligned) {
        *out_stransfer = &_aligned_strided_to_strided_datetime_cast;
    }
    else {
        *out_stransfer = &_strided_to_strided_datetime_cast;
    }
    *out_transferdata = (NpyAuxData *)data;

#if NPY_DT_DBG_TRACING
    printf("Dtype transfer from ");
    _safe_print((PyObject *)src_dtype);
    printf(" to ");
    _safe_print((PyObject *)dst_dtype);
    printf("\n");
    printf("has conversion fraction %lld/%lld\n", num, denom);
#endif


    return NPY_SUCCEED;
}