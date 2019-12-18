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
typedef  int /*<<< orphan*/  PyFortranObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyString_AsString (int /*<<< orphan*/ *) ; 
 scalar_t__ PyString_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyString_FromFormat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUnicode_FromFormat (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUnicode_FromString (char*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
fortran_repr(PyFortranObject *fp)
{
    PyObject *name = NULL, *repr = NULL;
    name = PyObject_GetAttrString((PyObject *)fp, "__name__");
    PyErr_Clear();
#if PY_VERSION_HEX >= 0x03000000
    if (name != NULL && PyUnicode_Check(name)) {
        repr = PyUnicode_FromFormat("<fortran %U>", name);
    }
    else {
        repr = PyUnicode_FromString("<fortran object>");
    }
#else
    if (name != NULL && PyString_Check(name)) {
        repr = PyString_FromFormat("<fortran %s>", PyString_AsString(name));
    }
    else {
        repr = PyString_FromString("<fortran object>");
    }
#endif
    Py_XDECREF(name);
    return repr;
}