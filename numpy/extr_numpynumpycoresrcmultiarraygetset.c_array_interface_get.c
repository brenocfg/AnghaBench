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
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyInt_FromLong (int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * array_dataptr_get (int /*<<< orphan*/ *) ; 
 scalar_t__ array_might_be_written (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * array_protocol_descr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * array_protocol_strides_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * array_shape_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arraydescr_protocol_typestr_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
array_interface_get(PyArrayObject *self)
{
    PyObject *dict;
    PyObject *obj;

    dict = PyDict_New();
    if (dict == NULL) {
        return NULL;
    }

    if (array_might_be_written(self) < 0) {
        Py_DECREF(dict);
        return NULL;
    }

    /* dataptr */
    obj = array_dataptr_get(self);
    PyDict_SetItemString(dict, "data", obj);
    Py_DECREF(obj);

    obj = array_protocol_strides_get(self);
    PyDict_SetItemString(dict, "strides", obj);
    Py_DECREF(obj);

    obj = array_protocol_descr_get(self);
    PyDict_SetItemString(dict, "descr", obj);
    Py_DECREF(obj);

    obj = arraydescr_protocol_typestr_get(PyArray_DESCR(self));
    PyDict_SetItemString(dict, "typestr", obj);
    Py_DECREF(obj);

    obj = array_shape_get(self);
    PyDict_SetItemString(dict, "shape", obj);
    Py_DECREF(obj);

    obj = PyInt_FromLong(3);
    PyDict_SetItemString(dict, "version", obj);
    Py_DECREF(obj);

    return dict;
}