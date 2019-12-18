#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ npy_intp ;
struct TYPE_23__ {int /*<<< orphan*/ * clone; int /*<<< orphan*/ * free; } ;
struct TYPE_24__ {int /*<<< orphan*/ * aip; int /*<<< orphan*/ * aop; int /*<<< orphan*/ * castfunc; TYPE_1__ base; } ;
typedef  TYPE_2__ _strided_cast_data ;
struct TYPE_25__ {scalar_t__ elsize; int type_num; int /*<<< orphan*/  byteorder; } ;
typedef  int /*<<< orphan*/  PyArray_VectorUnaryFunc ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  TYPE_3__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int NPY_DATETIME ; 
 int NPY_FAIL ; 
 int /*<<< orphan*/  NPY_NATIVE ; 
 int /*<<< orphan*/  NPY_NEEDS_PYAPI ; 
#define  NPY_OBJECT 131 
#define  NPY_STRING 130 
 int NPY_SUCCEED ; 
 int NPY_TIMEDELTA ; 
#define  NPY_UNICODE 129 
#define  NPY_VOID 128 
 TYPE_3__* PyArray_DescrNewByteorder (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyArray_GetCastFunc (TYPE_3__*,int) ; 
 scalar_t__ PyArray_ISNBO (int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_NewFromDescr_int (int /*<<< orphan*/ *,TYPE_3__*,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/  PyArray_free (TYPE_2__*) ; 
 scalar_t__ PyArray_malloc (int) ; 
 scalar_t__ PyDataType_FLAGCHK (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 scalar_t__ PyTypeNum_ISNUMBER (int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_3__*) ; 
 int /*<<< orphan*/ * _aligned_contig_to_contig_cast ; 
 int /*<<< orphan*/ * _aligned_strided_to_strided_cast ; 
 int /*<<< orphan*/ * _aligned_strided_to_strided_cast_decref_src ; 
 int /*<<< orphan*/  _strided_cast_data_clone ; 
 int /*<<< orphan*/  _strided_cast_data_free ; 
 int get_datetime_to_unicode_transfer_function (int,scalar_t__,scalar_t__,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*) ; 
 int get_nbo_cast_datetime_transfer_function (int,scalar_t__,scalar_t__,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int get_nbo_cast_numeric_transfer_function (int,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int get_nbo_datetime_to_string_transfer_function (int,scalar_t__,scalar_t__,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int get_nbo_string_to_datetime_transfer_function (int,scalar_t__,scalar_t__,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int get_unicode_to_datetime_transfer_function (int,scalar_t__,scalar_t__,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static int
get_nbo_cast_transfer_function(int aligned,
                            npy_intp src_stride, npy_intp dst_stride,
                            PyArray_Descr *src_dtype, PyArray_Descr *dst_dtype,
                            int move_references,
                            PyArray_StridedUnaryOp **out_stransfer,
                            NpyAuxData **out_transferdata,
                            int *out_needs_api,
                            int *out_needs_wrap)
{
    _strided_cast_data *data;
    PyArray_VectorUnaryFunc *castfunc;
    PyArray_Descr *tmp_dtype;
    npy_intp shape = 1, src_itemsize = src_dtype->elsize,
            dst_itemsize = dst_dtype->elsize;

    if (PyTypeNum_ISNUMBER(src_dtype->type_num) &&
                    PyTypeNum_ISNUMBER(dst_dtype->type_num)) {
        *out_needs_wrap = !PyArray_ISNBO(src_dtype->byteorder) ||
                          !PyArray_ISNBO(dst_dtype->byteorder);
        return get_nbo_cast_numeric_transfer_function(aligned,
                                    src_stride, dst_stride,
                                    src_dtype->type_num, dst_dtype->type_num,
                                    out_stransfer, out_transferdata);
    }

    if (src_dtype->type_num == NPY_DATETIME ||
            src_dtype->type_num == NPY_TIMEDELTA ||
            dst_dtype->type_num == NPY_DATETIME ||
            dst_dtype->type_num == NPY_TIMEDELTA) {
        /* A parameterized type, datetime->datetime sometimes needs casting */
        if ((src_dtype->type_num == NPY_DATETIME &&
                    dst_dtype->type_num == NPY_DATETIME) ||
                (src_dtype->type_num == NPY_TIMEDELTA &&
                    dst_dtype->type_num == NPY_TIMEDELTA)) {
            *out_needs_wrap = !PyArray_ISNBO(src_dtype->byteorder) ||
                              !PyArray_ISNBO(dst_dtype->byteorder);
            return get_nbo_cast_datetime_transfer_function(aligned,
                                        src_stride, dst_stride,
                                        src_dtype, dst_dtype,
                                        out_stransfer, out_transferdata);
        }

        /*
         * Datetime <-> string conversions can be handled specially.
         * The functions may raise an error if the strings have no
         * space, or can't be parsed properly.
         */
        if (src_dtype->type_num == NPY_DATETIME) {
            switch (dst_dtype->type_num) {
                case NPY_STRING:
                    *out_needs_api = 1;
                    *out_needs_wrap = !PyArray_ISNBO(src_dtype->byteorder);
                    return get_nbo_datetime_to_string_transfer_function(
                                        aligned,
                                        src_stride, dst_stride,
                                        src_dtype, dst_dtype,
                                        out_stransfer, out_transferdata);

                case NPY_UNICODE:
                    return get_datetime_to_unicode_transfer_function(
                                        aligned,
                                        src_stride, dst_stride,
                                        src_dtype, dst_dtype,
                                        out_stransfer, out_transferdata,
                                        out_needs_api);
            }
        }
        else if (dst_dtype->type_num == NPY_DATETIME) {
            switch (src_dtype->type_num) {
                case NPY_STRING:
                    *out_needs_api = 1;
                    *out_needs_wrap = !PyArray_ISNBO(dst_dtype->byteorder);
                    return get_nbo_string_to_datetime_transfer_function(
                                        aligned,
                                        src_stride, dst_stride,
                                        src_dtype, dst_dtype,
                                        out_stransfer, out_transferdata);

                case NPY_UNICODE:
                    return get_unicode_to_datetime_transfer_function(
                                        aligned,
                                        src_stride, dst_stride,
                                        src_dtype, dst_dtype,
                                        out_stransfer, out_transferdata,
                                        out_needs_api);
            }
        }
    }

    *out_needs_wrap = !aligned ||
                      !PyArray_ISNBO(src_dtype->byteorder) ||
                      !PyArray_ISNBO(dst_dtype->byteorder);

    /* Check the data types whose casting functions use API calls */
    switch (src_dtype->type_num) {
        case NPY_OBJECT:
        case NPY_STRING:
        case NPY_UNICODE:
        case NPY_VOID:
            if (out_needs_api) {
                *out_needs_api = 1;
            }
            break;
    }
    switch (dst_dtype->type_num) {
        case NPY_OBJECT:
        case NPY_STRING:
        case NPY_UNICODE:
        case NPY_VOID:
            if (out_needs_api) {
                *out_needs_api = 1;
            }
            break;
    }

    if (PyDataType_FLAGCHK(src_dtype, NPY_NEEDS_PYAPI) ||
            PyDataType_FLAGCHK(dst_dtype, NPY_NEEDS_PYAPI)) {
        if (out_needs_api) {
            *out_needs_api = 1;
        }
    }

    /* Get the cast function */
    castfunc = PyArray_GetCastFunc(src_dtype, dst_dtype->type_num);
    if (!castfunc) {
        *out_stransfer = NULL;
        *out_transferdata = NULL;
        return NPY_FAIL;
    }

    /* Allocate the data for the casting */
    data = (_strided_cast_data *)PyArray_malloc(sizeof(_strided_cast_data));
    if (data == NULL) {
        PyErr_NoMemory();
        *out_stransfer = NULL;
        *out_transferdata = NULL;
        return NPY_FAIL;
    }
    data->base.free = &_strided_cast_data_free;
    data->base.clone = &_strided_cast_data_clone;
    data->castfunc = castfunc;
    /*
     * TODO: This is a hack so the cast functions have an array.
     *       The cast functions shouldn't need that.  Also, since we
     *       always handle byte order conversions, this array should
     *       have native byte order.
     */
    if (PyArray_ISNBO(src_dtype->byteorder)) {
        tmp_dtype = src_dtype;
        Py_INCREF(tmp_dtype);
    }
    else {
        tmp_dtype = PyArray_DescrNewByteorder(src_dtype, NPY_NATIVE);
        if (tmp_dtype == NULL) {
            PyArray_free(data);
            return NPY_FAIL;
        }
    }
    data->aip = (PyArrayObject *)PyArray_NewFromDescr_int(
            &PyArray_Type, tmp_dtype,
            1, &shape, NULL, NULL,
            0, NULL, NULL,
            0, 1);
    if (data->aip == NULL) {
        PyArray_free(data);
        return NPY_FAIL;
    }
    /*
     * TODO: This is a hack so the cast functions have an array.
     *       The cast functions shouldn't need that.  Also, since we
     *       always handle byte order conversions, this array should
     *       have native byte order.
     */
    if (PyArray_ISNBO(dst_dtype->byteorder)) {
        tmp_dtype = dst_dtype;
        Py_INCREF(tmp_dtype);
    }
    else {
        tmp_dtype = PyArray_DescrNewByteorder(dst_dtype, NPY_NATIVE);
        if (tmp_dtype == NULL) {
            Py_DECREF(data->aip);
            PyArray_free(data);
            return NPY_FAIL;
        }
    }
    data->aop = (PyArrayObject *)PyArray_NewFromDescr_int(
            &PyArray_Type, tmp_dtype,
            1, &shape, NULL, NULL,
            0, NULL, NULL,
            0, 1);
    if (data->aop == NULL) {
        Py_DECREF(data->aip);
        PyArray_free(data);
        return NPY_FAIL;
    }

    /* If it's aligned and all native byte order, we're all done */
    if (move_references && src_dtype->type_num == NPY_OBJECT) {
        *out_stransfer = _aligned_strided_to_strided_cast_decref_src;
    }
    else {
        /*
         * Use the contig version if the strides are contiguous or
         * we're telling the caller to wrap the return, because
         * the wrapping uses a contiguous buffer.
         */
        if ((src_stride == src_itemsize && dst_stride == dst_itemsize) ||
                        *out_needs_wrap) {
            *out_stransfer = _aligned_contig_to_contig_cast;
        }
        else {
            *out_stransfer = _aligned_strided_to_strided_cast;
        }
    }
    *out_transferdata = (NpyAuxData *)data;

    return NPY_SUCCEED;
}