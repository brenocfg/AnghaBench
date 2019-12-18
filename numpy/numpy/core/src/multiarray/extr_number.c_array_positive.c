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
struct TYPE_2__ {int /*<<< orphan*/  positive; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ DEPRECATE (char*) ; 
 scalar_t__ PyArray_Copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_GenericInplaceUnaryFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyArray_GenericUnaryFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyArray_Return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Fetch (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_Restore (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyUFunc_HasOverride (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ can_elide_temp_unary (int /*<<< orphan*/ *) ; 
 TYPE_1__ n_ops ; 

__attribute__((used)) static PyObject *
array_positive(PyArrayObject *m1)
{
    /*
     * For backwards compatibility, where + just implied a copy,
     * we cannot just call n_ops.positive.  Instead, we do the following
     * 1. Try n_ops.positive
     * 2. If we get an exception, check whether __array_ufunc__ is
     *    overridden; if so, we live in the future and we allow the
     *    TypeError to be passed on.
     * 3. If not, give a deprecation warning and return a copy.
     */
    PyObject *value;
    if (can_elide_temp_unary(m1)) {
        value = PyArray_GenericInplaceUnaryFunction(m1, n_ops.positive);
    }
    else {
        value = PyArray_GenericUnaryFunction(m1, n_ops.positive);
    }
    if (value == NULL) {
        /*
         * We first fetch the error, as it needs to be clear to check
         * for the override.  When the deprecation is removed,
         * this whole stanza can be deleted.
         */
        PyObject *exc, *val, *tb;
        PyErr_Fetch(&exc, &val, &tb);
        if (PyUFunc_HasOverride((PyObject *)m1)) {
            PyErr_Restore(exc, val, tb);
            return NULL;
        }
        Py_XDECREF(exc);
        Py_XDECREF(val);
        Py_XDECREF(tb);

        /* 2018-06-28, 1.16.0 */
        if (DEPRECATE("Applying '+' to a non-numerical array is "
                      "ill-defined. Returning a copy, but in the future "
                      "this will error.") < 0) {
            return NULL;
        }
        value = PyArray_Return((PyArrayObject *)PyArray_Copy(m1));
    }
    return value;
}