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
 int /*<<< orphan*/ * PyObject_CallMethod (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
arraydescr_name_get(PyArray_Descr *self)
{
    /* let python handle this */
    PyObject *_numpy_dtype;
    PyObject *res;
    _numpy_dtype = PyImport_ImportModule("numpy.core._dtype");
    if (_numpy_dtype == NULL) {
        return NULL;
    }
    res = PyObject_CallMethod(_numpy_dtype, "_name_get", "O", self);
    Py_DECREF(_numpy_dtype);
    return res;
}