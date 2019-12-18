#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  npy_intp ;
struct TYPE_8__ {int /*<<< orphan*/  elsize; int /*<<< orphan*/  kind; } ;
struct TYPE_7__ {int two; int nd; int flags; int /*<<< orphan*/ * descr; int /*<<< orphan*/  data; int /*<<< orphan*/ * strides; int /*<<< orphan*/ * shape; int /*<<< orphan*/  itemsize; int /*<<< orphan*/  typekind; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_1__ PyArrayInterface ;

/* Variables and functions */
 int NPY_ARRAY_NOTSWAPPED ; 
 int NPY_ARRAY_OWNDATA ; 
 int NPY_ARRAY_UPDATEIFCOPY ; 
 int NPY_ARRAY_WRITEBACKIFCOPY ; 
 int NPY_ARR_HAS_DESCR ; 
 int /*<<< orphan*/ * NpyCapsule_FromVoidPtrAndDesc (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 TYPE_2__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISNOTSWAPPED (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISWRITEABLE (int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_free (TYPE_1__*) ; 
 scalar_t__ PyArray_malloc (int) ; 
 scalar_t__ PyDataType_HASFIELDS (TYPE_2__*) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 scalar_t__ array_might_be_written (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arraydescr_protocol_descr_get (TYPE_2__*) ; 
 int /*<<< orphan*/  gentype_struct_free ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static PyObject *
array_struct_get(PyArrayObject *self)
{
    PyArrayInterface *inter;
    PyObject *ret;

    if (PyArray_ISWRITEABLE(self)) {
        if (array_might_be_written(self) < 0) {
            return NULL;
        }
    }
    inter = (PyArrayInterface *)PyArray_malloc(sizeof(PyArrayInterface));
    if (inter==NULL) {
        return PyErr_NoMemory();
    }
    inter->two = 2;
    inter->nd = PyArray_NDIM(self);
    inter->typekind = PyArray_DESCR(self)->kind;
    inter->itemsize = PyArray_DESCR(self)->elsize;
    inter->flags = PyArray_FLAGS(self);
    /* reset unused flags */
    inter->flags &= ~(NPY_ARRAY_WRITEBACKIFCOPY | NPY_ARRAY_UPDATEIFCOPY |NPY_ARRAY_OWNDATA);
    if (PyArray_ISNOTSWAPPED(self)) inter->flags |= NPY_ARRAY_NOTSWAPPED;
    /*
     * Copy shape and strides over since these can be reset
     *when the array is "reshaped".
     */
    if (PyArray_NDIM(self) > 0) {
        inter->shape = (npy_intp *)PyArray_malloc(2*sizeof(npy_intp)*PyArray_NDIM(self));
        if (inter->shape == NULL) {
            PyArray_free(inter);
            return PyErr_NoMemory();
        }
        inter->strides = inter->shape + PyArray_NDIM(self);
        if (PyArray_NDIM(self)) {
            memcpy(inter->shape, PyArray_DIMS(self), sizeof(npy_intp)*PyArray_NDIM(self));
            memcpy(inter->strides, PyArray_STRIDES(self), sizeof(npy_intp)*PyArray_NDIM(self));
        }
    }
    else {
        inter->shape = NULL;
        inter->strides = NULL;
    }
    inter->data = PyArray_DATA(self);
    if (PyDataType_HASFIELDS(PyArray_DESCR(self))) {
        inter->descr = arraydescr_protocol_descr_get(PyArray_DESCR(self));
        if (inter->descr == NULL) {
            PyErr_Clear();
        }
        else {
            inter->flags &= NPY_ARR_HAS_DESCR;
        }
    }
    else {
        inter->descr = NULL;
    }
    Py_INCREF(self);
    ret = NpyCapsule_FromVoidPtrAndDesc(inter, self, gentype_struct_free);
    return ret;
}