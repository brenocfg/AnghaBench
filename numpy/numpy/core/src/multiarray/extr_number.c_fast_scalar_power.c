#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * square; int /*<<< orphan*/ * sqrt; int /*<<< orphan*/ * _ones_like; int /*<<< orphan*/ * reciprocal; int /*<<< orphan*/ * positive; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  scalar_t__ NPY_SCALARKIND ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_DOUBLE ; 
 scalar_t__ NPY_FLOAT_SCALAR ; 
 scalar_t__ PyArray_CastToType (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyArray_GenericInplaceUnaryFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_GenericUnaryFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISCOMPLEX (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISFLOAT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISFORTRAN (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISINTEGER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISOBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ can_elide_temp_unary (int /*<<< orphan*/ *) ; 
 scalar_t__ is_scalar_with_conversion (int /*<<< orphan*/ *,double*) ; 
 TYPE_1__ n_ops ; 

__attribute__((used)) static int
fast_scalar_power(PyArrayObject *a1, PyObject *o2, int inplace,
                  PyObject **value)
{
    double exponent;
    NPY_SCALARKIND kind;   /* NPY_NOSCALAR is not scalar */

    if (PyArray_Check(a1) &&
            !PyArray_ISOBJECT(a1) &&
            ((kind=is_scalar_with_conversion(o2, &exponent))>0)) {
        PyObject *fastop = NULL;
        if (PyArray_ISFLOAT(a1) || PyArray_ISCOMPLEX(a1)) {
            if (exponent == 1.0) {
                fastop = n_ops.positive;
            }
            else if (exponent == -1.0) {
                fastop = n_ops.reciprocal;
            }
            else if (exponent ==  0.0) {
                fastop = n_ops._ones_like;
            }
            else if (exponent ==  0.5) {
                fastop = n_ops.sqrt;
            }
            else if (exponent ==  2.0) {
                fastop = n_ops.square;
            }
            else {
                return -1;
            }

            if (inplace || can_elide_temp_unary(a1)) {
                *value = PyArray_GenericInplaceUnaryFunction(a1, fastop);
            }
            else {
                *value = PyArray_GenericUnaryFunction(a1, fastop);
            }
            return 0;
        }
        /* Because this is called with all arrays, we need to
         *  change the output if the kind of the scalar is different
         *  than that of the input and inplace is not on ---
         *  (thus, the input should be up-cast)
         */
        else if (exponent == 2.0) {
            fastop = n_ops.square;
            if (inplace) {
                *value = PyArray_GenericInplaceUnaryFunction(a1, fastop);
            }
            else {
                /* We only special-case the FLOAT_SCALAR and integer types */
                if (kind == NPY_FLOAT_SCALAR && PyArray_ISINTEGER(a1)) {
                    PyArray_Descr *dtype = PyArray_DescrFromType(NPY_DOUBLE);
                    a1 = (PyArrayObject *)PyArray_CastToType(a1, dtype,
                            PyArray_ISFORTRAN(a1));
                    if (a1 != NULL) {
                        /* cast always creates a new array */
                        *value = PyArray_GenericInplaceUnaryFunction(a1, fastop);
                        Py_DECREF(a1);
                    }
                }
                else {
                    *value = PyArray_GenericUnaryFunction(a1, fastop);
                }
            }
            return 0;
        }
    }
    /* no fast operation found */
    return -1;
}