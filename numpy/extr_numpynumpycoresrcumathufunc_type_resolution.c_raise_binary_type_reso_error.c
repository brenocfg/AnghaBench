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
typedef  int /*<<< orphan*/  PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyObject_Repr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUString_ConcatAndDel (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyUString_FromFormat (char*,char const*) ; 
 int /*<<< orphan*/  PyUString_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 char* ufunc_get_name_cstr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
raise_binary_type_reso_error(PyUFuncObject *ufunc, PyArrayObject **operands) {
    PyObject *errmsg;
    const char *ufunc_name = ufunc_get_name_cstr(ufunc);
    errmsg = PyUString_FromFormat("ufunc %s cannot use operands "
                        "with types ", ufunc_name);
    PyUString_ConcatAndDel(&errmsg,
            PyObject_Repr((PyObject *)PyArray_DESCR(operands[0])));
    PyUString_ConcatAndDel(&errmsg,
            PyUString_FromString(" and "));
    PyUString_ConcatAndDel(&errmsg,
            PyObject_Repr((PyObject *)PyArray_DESCR(operands[1])));
    PyErr_SetObject(PyExc_TypeError, errmsg);
    Py_DECREF(errmsg);
    return -1;
}