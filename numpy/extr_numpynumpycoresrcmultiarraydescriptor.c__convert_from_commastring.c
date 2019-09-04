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

/* Variables and functions */
 int NPY_FAIL ; 
 int PyArray_DescrConverter (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyBytes_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyImport_ImportModule (char*) ; 
 int /*<<< orphan*/  PyList_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyList_GET_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PyList_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_CallMethod (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _convert_from_list (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static PyArray_Descr *
_convert_from_commastring(PyObject *obj, int align)
{
    PyObject *listobj;
    PyArray_Descr *res;
    PyObject *_numpy_internal;

    if (!PyBytes_Check(obj)) {
        return NULL;
    }
    _numpy_internal = PyImport_ImportModule("numpy.core._internal");
    if (_numpy_internal == NULL) {
        return NULL;
    }
    listobj = PyObject_CallMethod(_numpy_internal, "_commastring", "O", obj);
    Py_DECREF(_numpy_internal);
    if (listobj == NULL) {
        return NULL;
    }
    if (!PyList_Check(listobj) || PyList_GET_SIZE(listobj) < 1) {
        PyErr_SetString(PyExc_RuntimeError,
                "_commastring is not returning a list with len >= 1");
        Py_DECREF(listobj);
        return NULL;
    }
    if (PyList_GET_SIZE(listobj) == 1) {
        int retcode;
        retcode = PyArray_DescrConverter(PyList_GET_ITEM(listobj, 0),
                                                &res);
        if (retcode == NPY_FAIL) {
            res = NULL;
        }
    }
    else {
        res = _convert_from_list(listobj, align);
    }
    Py_DECREF(listobj);
    if (!res && !PyErr_Occurred()) {
        PyErr_SetString(PyExc_ValueError,
                "invalid data-type");
        return NULL;
    }
    return res;
}