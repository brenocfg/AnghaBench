#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * PyArray_CastToType (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_CheckExact (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DescrConverter ; 
 scalar_t__ PyArray_EquivTypes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewFromDescrAndBase (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_getarray(PyArrayObject *self, PyObject *args)
{
    PyArray_Descr *newtype = NULL;
    PyObject *ret;

    if (!PyArg_ParseTuple(args, "|O&:__array__",
                            PyArray_DescrConverter, &newtype)) {
        Py_XDECREF(newtype);
        return NULL;
    }

    /* convert to PyArray_Type */
    if (!PyArray_CheckExact(self)) {
        PyArrayObject *new;

        Py_INCREF(PyArray_DESCR(self));
        new = (PyArrayObject *)PyArray_NewFromDescrAndBase(
                &PyArray_Type,
                PyArray_DESCR(self),
                PyArray_NDIM(self),
                PyArray_DIMS(self),
                PyArray_STRIDES(self),
                PyArray_DATA(self),
                PyArray_FLAGS(self),
                NULL,
                (PyObject *)self
        );
        if (new == NULL) {
            return NULL;
        }
        self = new;
    }
    else {
        Py_INCREF(self);
    }

    if ((newtype == NULL) || PyArray_EquivTypes(PyArray_DESCR(self), newtype)) {
        return (PyObject *)self;
    }
    else {
        ret = PyArray_CastToType(self, newtype, 0);
        Py_DECREF(self);
        return ret;
    }
}