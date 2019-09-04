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
typedef  int /*<<< orphan*/  npy_intp ;
typedef  int npy_int ;
struct TYPE_10__ {int dst_offset; scalar_t__ src_itemsize; scalar_t__ src_offset; int /*<<< orphan*/  data; int /*<<< orphan*/  stransfer; } ;
typedef  TYPE_2__ _single_field_transfer ;
struct TYPE_9__ {int /*<<< orphan*/ * clone; int /*<<< orphan*/ * free; } ;
struct TYPE_11__ {int field_count; TYPE_2__ fields; TYPE_1__ base; } ;
typedef  TYPE_3__ _field_transfer_data ;
struct TYPE_12__ {int /*<<< orphan*/  fields; int /*<<< orphan*/ * names; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  TYPE_4__ PyArray_Descr ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ ) ; 
 int NPY_FAIL ; 
 scalar_t__ NPY_SUCCEED ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,TYPE_4__**,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyArray_free (TYPE_3__*) ; 
 scalar_t__ PyArray_malloc (int) ; 
 int /*<<< orphan*/ * PyDict_GetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _field_transfer_data_clone ; 
 int /*<<< orphan*/  _field_transfer_data_free ; 
 int /*<<< orphan*/  _strided_to_strided_field_transfer ; 
 scalar_t__ get_setdstzero_transfer_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
get_setdestzero_fields_transfer_function(int aligned,
                            npy_intp dst_stride,
                            PyArray_Descr *dst_dtype,
                            PyArray_StridedUnaryOp **out_stransfer,
                            NpyAuxData **out_transferdata,
                            int *out_needs_api)
{
    PyObject *names, *key, *tup, *title;
    PyArray_Descr *dst_fld_dtype;
    npy_int i, names_size, field_count, structsize;
    int dst_offset;
    _field_transfer_data *data;
    _single_field_transfer *fields;

    names = dst_dtype->names;
    names_size = PyTuple_GET_SIZE(dst_dtype->names);

    field_count = names_size;
    structsize = sizeof(_field_transfer_data) +
                    field_count * sizeof(_single_field_transfer);
    /* Allocate the data and populate it */
    data = (_field_transfer_data *)PyArray_malloc(structsize);
    if (data == NULL) {
        PyErr_NoMemory();
        return NPY_FAIL;
    }
    data->base.free = &_field_transfer_data_free;
    data->base.clone = &_field_transfer_data_clone;
    fields = &data->fields;

    for (i = 0; i < names_size; ++i) {
        key = PyTuple_GET_ITEM(names, i);
        tup = PyDict_GetItem(dst_dtype->fields, key);
        if (!PyArg_ParseTuple(tup, "Oi|O", &dst_fld_dtype,
                                                &dst_offset, &title)) {
            PyArray_free(data);
            return NPY_FAIL;
        }
        if (get_setdstzero_transfer_function(0,
                                dst_stride,
                                dst_fld_dtype,
                                &fields[i].stransfer,
                                &fields[i].data,
                                out_needs_api) != NPY_SUCCEED) {
            for (i = i-1; i >= 0; --i) {
                NPY_AUXDATA_FREE(fields[i].data);
            }
            PyArray_free(data);
            return NPY_FAIL;
        }
        fields[i].src_offset = 0;
        fields[i].dst_offset = dst_offset;
        fields[i].src_itemsize = 0;
    }

    data->field_count = field_count;

    *out_stransfer = &_strided_to_strided_field_transfer;
    *out_transferdata = (NpyAuxData *)data;

    return NPY_SUCCEED;
}