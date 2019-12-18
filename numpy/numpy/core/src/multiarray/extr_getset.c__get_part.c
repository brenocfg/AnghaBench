#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type_num; int /*<<< orphan*/  byteorder; } ;
struct TYPE_8__ {int elsize; int /*<<< orphan*/  byteorder; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
#define  NPY_CDOUBLE 130 
#define  NPY_CFLOAT 129 
#define  NPY_CLONGDOUBLE 128 
 int NPY_DOUBLE ; 
 int NPY_FLOAT ; 
 int NPY_LONGDOUBLE ; 
 scalar_t__ PyArray_BYTES (int /*<<< orphan*/ *) ; 
 TYPE_7__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DIMS (int /*<<< orphan*/ *) ; 
 TYPE_1__* PyArray_DescrFromType (int) ; 
 TYPE_1__* PyArray_DescrNew (TYPE_1__*) ; 
 int /*<<< orphan*/  PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISNBO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewFromDescrAndBase (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_TYPE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyArrayObject *
_get_part(PyArrayObject *self, int imag)
{
    int float_type_num;
    PyArray_Descr *type;
    PyArrayObject *ret;
    int offset;

    switch (PyArray_DESCR(self)->type_num) {
        case NPY_CFLOAT:
            float_type_num = NPY_FLOAT;
            break;
        case NPY_CDOUBLE:
            float_type_num = NPY_DOUBLE;
            break;
        case NPY_CLONGDOUBLE:
            float_type_num = NPY_LONGDOUBLE;
            break;
        default:
            PyErr_Format(PyExc_ValueError,
                     "Cannot convert complex type number %d to float",
                     PyArray_DESCR(self)->type_num);
            return NULL;

    }
    type = PyArray_DescrFromType(float_type_num);

    offset = (imag ? type->elsize : 0);

    if (!PyArray_ISNBO(PyArray_DESCR(self)->byteorder)) {
        PyArray_Descr *new;
        new = PyArray_DescrNew(type);
        new->byteorder = PyArray_DESCR(self)->byteorder;
        Py_DECREF(type);
        type = new;
    }
    ret = (PyArrayObject *)PyArray_NewFromDescrAndBase(
            Py_TYPE(self),
            type,
            PyArray_NDIM(self),
            PyArray_DIMS(self),
            PyArray_STRIDES(self),
            PyArray_BYTES(self) + offset,
            PyArray_FLAGS(self), (PyObject *)self, (PyObject *)self);
    if (ret == NULL) {
        return NULL;
    }
    return ret;
}