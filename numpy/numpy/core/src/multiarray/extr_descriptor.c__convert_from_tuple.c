#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int npy_intp ;
struct TYPE_18__ {scalar_t__ type_num; int elsize; TYPE_10__* subarray; struct TYPE_18__* names; struct TYPE_18__* fields; int /*<<< orphan*/  alignment; int /*<<< orphan*/  flags; scalar_t__ metadata; } ;
struct TYPE_17__ {int member_1; int len; int* ptr; int /*<<< orphan*/ * member_0; } ;
struct TYPE_16__ {int /*<<< orphan*/ * shape; TYPE_2__* base; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Dims ;
typedef  TYPE_2__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArray_ArrayDescr ;

/* Variables and functions */
 scalar_t__ DEPRECATE_FUTUREWARNING (char*) ; 
 int NPY_MAXDIMS ; 
 int NPY_MAX_INT ; 
 scalar_t__ NPY_UNICODE ; 
 int /*<<< orphan*/  NPY_VOID ; 
 int /*<<< orphan*/  PyArray_DESCR_REPLACE (TYPE_2__*) ; 
 int /*<<< orphan*/  PyArray_DescrAlignConverter (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  PyArray_DescrConverter (int /*<<< orphan*/ *,TYPE_2__**) ; 
 TYPE_2__* PyArray_DescrNewFromType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_IntpConverter (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int PyArray_OverflowMultiplyList (int*,int) ; 
 int PyArray_PyIntAsInt (int /*<<< orphan*/ *) ; 
 TYPE_10__* PyArray_malloc (int) ; 
 scalar_t__ PyDataType_ISUNSIZED (TYPE_2__*) ; 
 scalar_t__ PyDictProxy_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyDict_Check (int /*<<< orphan*/ *) ; 
 int PyDict_Merge (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyInt_FromLong (long) ; 
 scalar_t__ PyNumber_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_2__*) ; 
 int /*<<< orphan*/  Py_XDECREF (TYPE_2__*) ; 
 TYPE_2__* _use_inherit (TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ error_converting (int) ; 
 int /*<<< orphan*/  npy_free_cache_dim_obj (TYPE_1__) ; 
 int npy_mul_with_overflow_int (int*,int,int) ; 

__attribute__((used)) static PyArray_Descr *
_convert_from_tuple(PyObject *obj, int align)
{
    PyArray_Descr *type, *res;
    PyObject *val;
    int errflag;

    if (PyTuple_GET_SIZE(obj) != 2) {
        return NULL;
    }
    if (align) {
        if (!PyArray_DescrAlignConverter(PyTuple_GET_ITEM(obj, 0), &type)) {
            return NULL;
        }
    }
    else {
        if (!PyArray_DescrConverter(PyTuple_GET_ITEM(obj, 0), &type)) {
            return NULL;
        }
    }    
    val = PyTuple_GET_ITEM(obj,1);
    /* try to interpret next item as a type */
    res = _use_inherit(type, val, &errflag);
    if (res || errflag) {
        Py_DECREF(type);
        return res;
    }
    PyErr_Clear();
    /*
     * We get here if res was NULL but errflag wasn't set
     * --- i.e. the conversion to a data-descr failed in _use_inherit
     */
    if (PyDataType_ISUNSIZED(type)) {
        /* interpret next item as a typesize */
        int itemsize = PyArray_PyIntAsInt(PyTuple_GET_ITEM(obj,1));

        if (error_converting(itemsize)) {
            PyErr_SetString(PyExc_ValueError,
                    "invalid itemsize in generic type tuple");
            Py_DECREF(type);
            return NULL;
        }
        PyArray_DESCR_REPLACE(type);
        if (type == NULL) {
            return NULL;
        }
        if (type->type_num == NPY_UNICODE) {
            type->elsize = itemsize << 2;
        }
        else {
            type->elsize = itemsize;
        }
        return type;
    }
    else if (type->metadata && (PyDict_Check(val) || PyDictProxy_Check(val))) {
        /* Assume it's a metadata dictionary */
        if (PyDict_Merge(type->metadata, val, 0) == -1) {
            Py_DECREF(type);
            return NULL;
        }
        return type;
    }
    else {
        /*
         * interpret next item as shape (if it's a tuple)
         * and reset the type to NPY_VOID with
         * a new fields attribute.
         */
        PyArray_Dims shape = {NULL, -1};
        PyArray_Descr *newdescr = NULL;
        npy_intp items;
        int i, overflowed;
        int nbytes;

        if (!(PyArray_IntpConverter(val, &shape)) || (shape.len > NPY_MAXDIMS)) {
            PyErr_SetString(PyExc_ValueError,
                    "invalid shape in fixed-type tuple.");
            goto fail;
        }
        /* if (type, ()) was given it is equivalent to type... */
        if (shape.len == 0 && PyTuple_Check(val)) {
            npy_free_cache_dim_obj(shape);
            return type;
        }
        /* (type, 1) use to be equivalent to type, but is deprecated */
        if (shape.len == 1
                && shape.ptr[0] == 1
                && PyNumber_Check(val)) {
            /* 2019-05-20, 1.17 */
            if (DEPRECATE_FUTUREWARNING(
                        "Passing (type, 1) or '1type' as a synonym of type is "
                        "deprecated; in a future version of numpy, it will be "
                        "understood as (type, (1,)) / '(1,)type'.") < 0) {
                goto fail;
            }
            npy_free_cache_dim_obj(shape);
            return type;
        }

        /* validate and set shape */
        for (i=0; i < shape.len; i++) {
            if (shape.ptr[i] < 0) {
                PyErr_SetString(PyExc_ValueError,
                                "invalid shape in fixed-type tuple: "
                                "dimension smaller then zero.");
                goto fail;
            }
            if (shape.ptr[i] > NPY_MAX_INT) {
                PyErr_SetString(PyExc_ValueError,
                                "invalid shape in fixed-type tuple: "
                                "dimension does not fit into a C int.");
                goto fail;
            }
        }
        items = PyArray_OverflowMultiplyList(shape.ptr, shape.len);
        if (items < 0 || items > NPY_MAX_INT) {
            overflowed = 1;
        }
        else {
            overflowed = npy_mul_with_overflow_int(
                &nbytes, type->elsize, (int) items);
        }
        if (overflowed) {
            PyErr_SetString(PyExc_ValueError,
                            "invalid shape in fixed-type tuple: dtype size in "
                            "bytes must fit into a C int.");
            goto fail;
        }
        newdescr = PyArray_DescrNewFromType(NPY_VOID);
        if (newdescr == NULL) {
            goto fail;
        }
        newdescr->elsize = nbytes;
        newdescr->subarray = PyArray_malloc(sizeof(PyArray_ArrayDescr));
        if (newdescr->subarray == NULL) {
            PyErr_NoMemory();
            goto fail;
        }
        newdescr->flags = type->flags;
        newdescr->alignment = type->alignment;
        newdescr->subarray->base = type;
        type = NULL;
        Py_XDECREF(newdescr->fields);
        Py_XDECREF(newdescr->names);
        newdescr->fields = NULL;
        newdescr->names = NULL;

        /*
         * Create a new subarray->shape tuple (it can be an arbitrary
         * sequence of integer like objects, neither of which is safe.
         */
        newdescr->subarray->shape = PyTuple_New(shape.len);
        if (newdescr->subarray->shape == NULL) {
            goto fail;
        }
        for (i=0; i < shape.len; i++) {
            PyTuple_SET_ITEM(newdescr->subarray->shape, i,
                             PyInt_FromLong((long)shape.ptr[i]));

            if (PyTuple_GET_ITEM(newdescr->subarray->shape, i) == NULL) {
                goto fail;
            }
        }

        npy_free_cache_dim_obj(shape);
        return newdescr;

    fail:
        Py_XDECREF(type);
        Py_XDECREF(newdescr);
        npy_free_cache_dim_obj(shape);
        return NULL;
    }
}