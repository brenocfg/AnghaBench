#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ npy_intp ;
struct TYPE_30__ {int nd; char* data; int /*<<< orphan*/ * base; TYPE_2__* descr; int /*<<< orphan*/  flags; int /*<<< orphan*/ * strides; int /*<<< orphan*/ * dimensions; } ;
struct TYPE_29__ {scalar_t__ elsize; scalar_t__ byteorder; int /*<<< orphan*/  type_num; TYPE_1__* f; } ;
struct TYPE_28__ {int /*<<< orphan*/  (* copyswapn ) (int /*<<< orphan*/ *,scalar_t__,char*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ Py_ssize_t ;
typedef  TYPE_2__ PyObject ;
typedef  TYPE_2__ PyArray_Descr ;
typedef  TYPE_4__ PyArrayObject_fields ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  IsAligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NPY_ARRAY_C_CONTIGUOUS ; 
 int /*<<< orphan*/  NPY_ARRAY_DEFAULT ; 
 int /*<<< orphan*/  NPY_ARRAY_F_CONTIGUOUS ; 
 int NPY_ARRAY_OWNDATA ; 
 int NPY_ARRAY_UPDATEIFCOPY ; 
 int /*<<< orphan*/  NPY_ARRAY_UPDATE_ALL ; 
 int NPY_ARRAY_WRITEBACKIFCOPY ; 
 scalar_t__ NPY_BIG ; 
 int /*<<< orphan*/  NPY_LIST_PICKLE ; 
 scalar_t__ NPY_LITTLE ; 
 int NPY_MAXDIMS ; 
 int /*<<< orphan*/  NPY_NEEDS_INIT ; 
 int /*<<< orphan*/  PyArg_ParseTuple (TYPE_2__*,char*,int*,TYPE_2__**,TYPE_2__**,TYPE_2__**,...) ; 
 int /*<<< orphan*/  PyArrayDescr_Type ; 
 TYPE_2__* PyArray_BASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_CLEARFLAGS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PyArray_DATA (int /*<<< orphan*/ *) ; 
 TYPE_2__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_DIMS (int /*<<< orphan*/ *) ; 
 TYPE_2__* PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 TYPE_2__* PyArray_DescrNew (TYPE_2__*) ; 
 int /*<<< orphan*/  PyArray_ENABLEFLAGS (int /*<<< orphan*/ *,int) ; 
 int PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 int PyArray_ISBYTESWAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISEXTENDED (int /*<<< orphan*/ *) ; 
 int PyArray_IntpFromSequence (TYPE_2__*,scalar_t__*,int) ; 
 scalar_t__ PyArray_MultiplyList (scalar_t__*,int) ; 
 scalar_t__ PyArray_NBYTES (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SetBaseObject (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  PyArray_UpdateFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PyBytes_AsStringAndSize (TYPE_2__*,char**,scalar_t__*) ; 
 int /*<<< orphan*/  PyBytes_Check (TYPE_2__*) ; 
 int /*<<< orphan*/  PyDataMem_FREE (int /*<<< orphan*/ *) ; 
 void* PyDataMem_NEW (scalar_t__) ; 
 scalar_t__ PyDataType_FLAGCHK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyList_Check (TYPE_2__*) ; 
 scalar_t__ PyString_CHECK_INTERNED (TYPE_2__*) ; 
 int /*<<< orphan*/  PyTuple_Type ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_2__*) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_2__*) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  Py_XDECREF (TYPE_2__*) ; 
 int /*<<< orphan*/  _array_fill_strides (int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _setlist_pkl (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * npy_alloc_cache_dim (int) ; 
 int /*<<< orphan*/  npy_free_cache_dim_array (int /*<<< orphan*/ *) ; 
 int npy_mul_with_overflow_intp (scalar_t__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,scalar_t__,char*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_setstate(PyArrayObject *self, PyObject *args)
{
    PyObject *shape;
    PyArray_Descr *typecode;
    int version = 1;
    int is_f_order;
    PyObject *rawdata = NULL;
    char *datastr;
    Py_ssize_t len;
    npy_intp size, dimensions[NPY_MAXDIMS];
    int nd;
    npy_intp nbytes;
    int overflowed;

    PyArrayObject_fields *fa = (PyArrayObject_fields *)self;

    /* This will free any memory associated with a and
       use the string in setstate as the (writeable) memory.
    */
    if (!PyArg_ParseTuple(args, "(iO!O!iO):__setstate__",
                            &version,
                            &PyTuple_Type, &shape,
                            &PyArrayDescr_Type, &typecode,
                            &is_f_order,
                            &rawdata)) {
        PyErr_Clear();
        version = 0;
        if (!PyArg_ParseTuple(args, "(O!O!iO):__setstate__",
                            &PyTuple_Type, &shape,
                            &PyArrayDescr_Type, &typecode,
                            &is_f_order,
                            &rawdata)) {
            return NULL;
        }
    }

    /* If we ever need another pickle format, increment the version
       number. But we should still be able to handle the old versions.
       We've only got one right now. */
    if (version != 1 && version != 0) {
        PyErr_Format(PyExc_ValueError,
                     "can't handle version %d of numpy.ndarray pickle",
                     version);
        return NULL;
    }

    Py_XDECREF(PyArray_DESCR(self));
    fa->descr = typecode;
    Py_INCREF(typecode);
    nd = PyArray_IntpFromSequence(shape, dimensions, NPY_MAXDIMS);
    if (nd < 0) {
        return NULL;
    }
    size = PyArray_MultiplyList(dimensions, nd);
    if (size < 0) {
        /* More items than are addressable */
        return PyErr_NoMemory();
    }
    overflowed = npy_mul_with_overflow_intp(
        &nbytes, size, PyArray_DESCR(self)->elsize);
    if (overflowed) {
        /* More bytes than are addressable */
        return PyErr_NoMemory();
    }

    if (PyDataType_FLAGCHK(typecode, NPY_LIST_PICKLE)) {
        if (!PyList_Check(rawdata)) {
            PyErr_SetString(PyExc_TypeError,
                            "object pickle not returning list");
            return NULL;
        }
    }
    else {
        Py_INCREF(rawdata);

#if defined(NPY_PY3K)
        /* Backward compatibility with Python 2 NumPy pickles */
        if (PyUnicode_Check(rawdata)) {
            PyObject *tmp;
            tmp = PyUnicode_AsLatin1String(rawdata);
            Py_DECREF(rawdata);
            rawdata = tmp;
            if (tmp == NULL) {
                /* More informative error message */
                PyErr_SetString(PyExc_ValueError,
                                ("Failed to encode latin1 string when unpickling a Numpy array. "
                                 "pickle.load(a, encoding='latin1') is assumed."));
                return NULL;
            }
        }
#endif

        if (!PyBytes_Check(rawdata)) {
            PyErr_SetString(PyExc_TypeError,
                            "pickle not returning string");
            Py_DECREF(rawdata);
            return NULL;
        }

        if (PyBytes_AsStringAndSize(rawdata, &datastr, &len) < 0) {
            Py_DECREF(rawdata);
            return NULL;
        }

        if (len != nbytes) {
            PyErr_SetString(PyExc_ValueError,
                            "buffer size does not"  \
                            " match array size");
            Py_DECREF(rawdata);
            return NULL;
        }
    }

    if ((PyArray_FLAGS(self) & NPY_ARRAY_OWNDATA)) {
        PyDataMem_FREE(PyArray_DATA(self));
        PyArray_CLEARFLAGS(self, NPY_ARRAY_OWNDATA);
    }
    Py_XDECREF(PyArray_BASE(self));
    fa->base = NULL;

    PyArray_CLEARFLAGS(self, NPY_ARRAY_WRITEBACKIFCOPY);
    PyArray_CLEARFLAGS(self, NPY_ARRAY_UPDATEIFCOPY);

    if (PyArray_DIMS(self) != NULL) {
        npy_free_cache_dim_array(self);
        fa->dimensions = NULL;
    }

    fa->flags = NPY_ARRAY_DEFAULT;

    fa->nd = nd;

    if (nd > 0) {
        fa->dimensions = npy_alloc_cache_dim(3*nd);
        if (fa->dimensions == NULL) {
            return PyErr_NoMemory();
        }
        fa->strides = PyArray_DIMS(self) + nd;
        memcpy(PyArray_DIMS(self), dimensions, sizeof(npy_intp)*nd);
        _array_fill_strides(PyArray_STRIDES(self), dimensions, nd,
                               PyArray_DESCR(self)->elsize,
                               (is_f_order ? NPY_ARRAY_F_CONTIGUOUS :
                                             NPY_ARRAY_C_CONTIGUOUS),
                               &(fa->flags));
    }

    if (!PyDataType_FLAGCHK(typecode, NPY_LIST_PICKLE)) {
        int swap = PyArray_ISBYTESWAPPED(self);
        fa->data = datastr;
#ifndef NPY_PY3K
        /* Check that the string is not interned */
        if (!IsAligned(self) || swap || PyString_CHECK_INTERNED(rawdata)) {
#else
        /* Bytes should always be considered immutable, but we just grab the
         * pointer if they are large, to save memory. */
        if (!IsAligned(self) || swap || (len <= 1000)) {
#endif
            npy_intp num = PyArray_NBYTES(self);
            fa->data = PyDataMem_NEW(num);
            if (PyArray_DATA(self) == NULL) {
                fa->nd = 0;
                npy_free_cache_dim_array(self);
                Py_DECREF(rawdata);
                return PyErr_NoMemory();
            }
            if (swap) {
                /* byte-swap on pickle-read */
                npy_intp numels = PyArray_SIZE(self);
                PyArray_DESCR(self)->f->copyswapn(PyArray_DATA(self),
                                        PyArray_DESCR(self)->elsize,
                                        datastr, PyArray_DESCR(self)->elsize,
                                        numels, 1, self);
                if (!PyArray_ISEXTENDED(self)) {
                    fa->descr = PyArray_DescrFromType(
                                    PyArray_DESCR(self)->type_num);
                }
                else {
                    fa->descr = PyArray_DescrNew(typecode);
                    if (PyArray_DESCR(self)->byteorder == NPY_BIG) {
                        PyArray_DESCR(self)->byteorder = NPY_LITTLE;
                    }
                    else if (PyArray_DESCR(self)->byteorder == NPY_LITTLE) {
                        PyArray_DESCR(self)->byteorder = NPY_BIG;
                    }
                }
                Py_DECREF(typecode);
            }
            else {
                memcpy(PyArray_DATA(self), datastr, num);
            }
            PyArray_ENABLEFLAGS(self, NPY_ARRAY_OWNDATA);
            fa->base = NULL;
            Py_DECREF(rawdata);
        }
        else {
            if (PyArray_SetBaseObject(self, rawdata) < 0) {
                return NULL;
            }
        }
    }
    else {
        fa->data = PyDataMem_NEW(PyArray_NBYTES(self));
        if (PyArray_DATA(self) == NULL) {
            fa->nd = 0;
            fa->data = PyDataMem_NEW(PyArray_DESCR(self)->elsize);
            npy_free_cache_dim_array(self);
            return PyErr_NoMemory();
        }
        if (PyDataType_FLAGCHK(PyArray_DESCR(self), NPY_NEEDS_INIT)) {
            memset(PyArray_DATA(self), 0, PyArray_NBYTES(self));
        }
        PyArray_ENABLEFLAGS(self, NPY_ARRAY_OWNDATA);
        fa->base = NULL;
        if (_setlist_pkl(self, rawdata) < 0) {
            return NULL;
        }
    }

    PyArray_UpdateFlags(self, NPY_ARRAY_UPDATE_ALL);

    Py_RETURN_NONE;
}