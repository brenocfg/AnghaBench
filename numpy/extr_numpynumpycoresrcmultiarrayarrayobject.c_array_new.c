#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ npy_longlong ;
typedef  int npy_intp ;
struct TYPE_15__ {int len; int flags; int /*<<< orphan*/ * base; int /*<<< orphan*/ * ptr; } ;
struct TYPE_14__ {int elsize; } ;
struct TYPE_13__ {int* ptr; int len; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Dims ;
typedef  TYPE_2__ PyArray_Descr ;
typedef  TYPE_3__ PyArray_Chunk ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  scalar_t__ NPY_ORDER ;

/* Variables and functions */
 int NPY_ARRAY_F_CONTIGUOUS ; 
 scalar_t__ NPY_CORDER ; 
 int /*<<< orphan*/  NPY_DEFAULT_TYPE ; 
 scalar_t__ NPY_FORTRANORDER ; 
 int /*<<< orphan*/  NPY_ITEM_HASOBJECT ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  PyArray_BufferConverter ; 
 int /*<<< orphan*/  PyArray_CheckStrides (int,int,int,int,int*,int*) ; 
 int /*<<< orphan*/  PyArray_DescrConverter ; 
 TYPE_2__* PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_FillObjectArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_IntpConverter ; 
 int PyArray_MultiplyList (int*,int) ; 
 scalar_t__ PyArray_NewFromDescr_int (int /*<<< orphan*/ *,TYPE_2__*,int,int*,int*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PyArray_OrderConverter ; 
 scalar_t__ PyDataType_FLAGCHK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_None ; 
 int /*<<< orphan*/  Py_XDECREF (TYPE_2__*) ; 
 int /*<<< orphan*/  npy_free_cache_dim_obj (TYPE_1__) ; 

__attribute__((used)) static PyObject *
array_new(PyTypeObject *subtype, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"shape", "dtype", "buffer", "offset", "strides",
                             "order", NULL};
    PyArray_Descr *descr = NULL;
    int itemsize;
    PyArray_Dims dims = {NULL, 0};
    PyArray_Dims strides = {NULL, 0};
    PyArray_Chunk buffer;
    npy_longlong offset = 0;
    NPY_ORDER order = NPY_CORDER;
    int is_f_order = 0;
    PyArrayObject *ret;

    buffer.ptr = NULL;
    /*
     * Usually called with shape and type but can also be called with buffer,
     * strides, and swapped info For now, let's just use this to create an
     * empty, contiguous array of a specific type and shape.
     */
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&|O&O&LO&O&:ndarray",
                                     kwlist, PyArray_IntpConverter,
                                     &dims,
                                     PyArray_DescrConverter,
                                     &descr,
                                     PyArray_BufferConverter,
                                     &buffer,
                                     &offset,
                                     &PyArray_IntpConverter,
                                     &strides,
                                     &PyArray_OrderConverter,
                                     &order)) {
        goto fail;
    }
    if (order == NPY_FORTRANORDER) {
        is_f_order = 1;
    }
    if (descr == NULL) {
        descr = PyArray_DescrFromType(NPY_DEFAULT_TYPE);
    }

    itemsize = descr->elsize;

    if (strides.ptr != NULL) {
        npy_intp nb, off;
        if (strides.len != dims.len) {
            PyErr_SetString(PyExc_ValueError,
                            "strides, if given, must be "   \
                            "the same length as shape");
            goto fail;
        }

        if (buffer.ptr == NULL) {
            nb = 0;
            off = 0;
        }
        else {
            nb = buffer.len;
            off = (npy_intp) offset;
        }


        if (!PyArray_CheckStrides(itemsize, dims.len,
                                  nb, off,
                                  dims.ptr, strides.ptr)) {
            PyErr_SetString(PyExc_ValueError,
                            "strides is incompatible "      \
                            "with shape of requested "      \
                            "array and size of buffer");
            goto fail;
        }
    }

    if (buffer.ptr == NULL) {
        ret = (PyArrayObject *)
            PyArray_NewFromDescr_int(subtype, descr,
                                     (int)dims.len,
                                     dims.ptr,
                                     strides.ptr, NULL, is_f_order, NULL, NULL,
                                     0, 1);
        if (ret == NULL) {
            descr = NULL;
            goto fail;
        }
        if (PyDataType_FLAGCHK(descr, NPY_ITEM_HASOBJECT)) {
            /* place Py_None in object positions */
            PyArray_FillObjectArray(ret, Py_None);
            if (PyErr_Occurred()) {
                descr = NULL;
                goto fail;
            }
        }
    }
    else {
        /* buffer given -- use it */
        if (dims.len == 1 && dims.ptr[0] == -1) {
            dims.ptr[0] = (buffer.len-(npy_intp)offset) / itemsize;
        }
        else if ((strides.ptr == NULL) &&
                 (buffer.len < (offset + (((npy_intp)itemsize)*
                                          PyArray_MultiplyList(dims.ptr,
                                                               dims.len))))) {
            PyErr_SetString(PyExc_TypeError,
                            "buffer is too small for "      \
                            "requested array");
            goto fail;
        }
        /* get writeable and aligned */
        if (is_f_order) {
            buffer.flags |= NPY_ARRAY_F_CONTIGUOUS;
        }
        ret = (PyArrayObject *)PyArray_NewFromDescr_int(
                subtype, descr,
                dims.len, dims.ptr, strides.ptr, offset + (char *)buffer.ptr,
                buffer.flags, NULL, buffer.base,
                0, 1);
        if (ret == NULL) {
            descr = NULL;
            goto fail;
        }
    }

    npy_free_cache_dim_obj(dims);
    npy_free_cache_dim_obj(strides);
    return (PyObject *)ret;

 fail:
    Py_XDECREF(descr);
    npy_free_cache_dim_obj(dims);
    npy_free_cache_dim_obj(strides);
    return NULL;
}