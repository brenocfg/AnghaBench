#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* tp_as_number; } ;
struct TYPE_3__ {int /*<<< orphan*/ * (* nb_float ) (int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  NPY_SCALARKIND ;

/* Variables and functions */
 int /*<<< orphan*/  Floating ; 
 int /*<<< orphan*/  Integer ; 
 int /*<<< orphan*/  NPY_FLOAT_SCALAR ; 
 int /*<<< orphan*/  NPY_INTPOS_SCALAR ; 
 int /*<<< orphan*/  NPY_NOSCALAR ; 
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISFLOAT (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISINTEGER (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_IsScalar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_Occurred () ; 
 double PyFloat_AsDouble (int /*<<< orphan*/ *) ; 
 scalar_t__ PyFloat_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyIndex_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_AsLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_AsSsize_t (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyNumber_Index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 TYPE_2__* Py_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ error_converting (scalar_t__) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static NPY_SCALARKIND
is_scalar_with_conversion(PyObject *o2, double* out_exponent)
{
    PyObject *temp;
    const int optimize_fpexps = 1;

    if (PyInt_Check(o2)) {
        *out_exponent = (double)PyInt_AsLong(o2);
        return NPY_INTPOS_SCALAR;
    }
    if (optimize_fpexps && PyFloat_Check(o2)) {
        *out_exponent = PyFloat_AsDouble(o2);
        return NPY_FLOAT_SCALAR;
    }
    if (PyArray_Check(o2)) {
        if ((PyArray_NDIM((PyArrayObject *)o2) == 0) &&
                ((PyArray_ISINTEGER((PyArrayObject *)o2) ||
                 (optimize_fpexps && PyArray_ISFLOAT((PyArrayObject *)o2))))) {
            temp = Py_TYPE(o2)->tp_as_number->nb_float(o2);
            if (temp == NULL) {
                return NPY_NOSCALAR;
            }
            *out_exponent = PyFloat_AsDouble(o2);
            Py_DECREF(temp);
            if (PyArray_ISINTEGER((PyArrayObject *)o2)) {
                return NPY_INTPOS_SCALAR;
            }
            else { /* ISFLOAT */
                return NPY_FLOAT_SCALAR;
            }
        }
    }
    else if (PyArray_IsScalar(o2, Integer) ||
                (optimize_fpexps && PyArray_IsScalar(o2, Floating))) {
        temp = Py_TYPE(o2)->tp_as_number->nb_float(o2);
        if (temp == NULL) {
            return NPY_NOSCALAR;
        }
        *out_exponent = PyFloat_AsDouble(o2);
        Py_DECREF(temp);

        if (PyArray_IsScalar(o2, Integer)) {
                return NPY_INTPOS_SCALAR;
        }
        else { /* IsScalar(o2, Floating) */
            return NPY_FLOAT_SCALAR;
        }
    }
    else if (PyIndex_Check(o2)) {
        PyObject* value = PyNumber_Index(o2);
        Py_ssize_t val;
        if (value==NULL) {
            if (PyErr_Occurred()) {
                PyErr_Clear();
            }
            return NPY_NOSCALAR;
        }
        val = PyInt_AsSsize_t(value);
        if (error_converting(val)) {
            PyErr_Clear();
            return NPY_NOSCALAR;
        }
        *out_exponent = (double) val;
        return NPY_INTPOS_SCALAR;
    }
    return NPY_NOSCALAR;
}