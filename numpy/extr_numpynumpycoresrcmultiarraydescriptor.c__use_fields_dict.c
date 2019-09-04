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
 int /*<<< orphan*/ * PyImport_ImportModule (char*) ; 
 scalar_t__ PyObject_CallMethod (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyArray_Descr *
_use_fields_dict(PyObject *obj, int align)
{
    PyObject *_numpy_internal;
    PyArray_Descr *res;

    _numpy_internal = PyImport_ImportModule("numpy.core._internal");
    if (_numpy_internal == NULL) {
        return NULL;
    }
    res = (PyArray_Descr *)PyObject_CallMethod(_numpy_internal,
            "_usefields", "Oi", obj, align);
    Py_DECREF(_numpy_internal);
    return res;
}