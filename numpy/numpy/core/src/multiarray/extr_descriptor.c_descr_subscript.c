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
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_PyIntAsIntp (int /*<<< orphan*/ *) ; 
 scalar_t__ PyBaseString_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_GivenExceptionMatches (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 scalar_t__ _check_has_fields (int /*<<< orphan*/ *) ; 
 scalar_t__ _is_list_of_strings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _subscript_by_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _subscript_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ arraydescr_field_subset_view (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ error_converting (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
descr_subscript(PyArray_Descr *self, PyObject *op)
{
    if (_check_has_fields(self) < 0) {
        return NULL;
    }

    if (PyBaseString_Check(op)) {
        return _subscript_by_name(self, op);
    }
    else if (_is_list_of_strings(op)) {
        return (PyObject *)arraydescr_field_subset_view(self, op);
    }
    else {
        Py_ssize_t i = PyArray_PyIntAsIntp(op);
        if (error_converting(i)) {
            /* if converting to an int gives a type error, adjust the message */
            PyObject *err = PyErr_Occurred();
            if (PyErr_GivenExceptionMatches(err, PyExc_TypeError)) {
                PyErr_SetString(PyExc_TypeError,
                        "Field key must be an integer field offset, "
                        "single field name, or list of field names.");
            }
            return NULL;
        }
        return _subscript_by_index(self, i);
    }
}