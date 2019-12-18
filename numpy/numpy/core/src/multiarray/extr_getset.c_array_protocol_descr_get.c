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
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/ * PyList_New (int) ; 
 int /*<<< orphan*/  PyList_SET_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyString_FromString (char*) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_typestr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arraydescr_protocol_descr_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
array_protocol_descr_get(PyArrayObject *self)
{
    PyObject *res;
    PyObject *dobj;

    res = arraydescr_protocol_descr_get(PyArray_DESCR(self));
    if (res) {
        return res;
    }
    PyErr_Clear();

    /* get default */
    dobj = PyTuple_New(2);
    if (dobj == NULL) {
        return NULL;
    }
    PyTuple_SET_ITEM(dobj, 0, PyString_FromString(""));
    PyTuple_SET_ITEM(dobj, 1, array_typestr_get(self));
    res = PyList_New(1);
    if (res == NULL) {
        Py_DECREF(dobj);
        return NULL;
    }
    PyList_SET_ITEM(res, 0, dobj);
    return res;
}