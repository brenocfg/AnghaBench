#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* descr; } ;
struct TYPE_9__ {int /*<<< orphan*/ * names; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  TYPE_2__ PyArrayObject_fields ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  NPY_SELECTKIND ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ARRAY_DEFAULT ; 
 int /*<<< orphan*/  NPY_INTROSELECT ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * PyArray_ArgPartition (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_AxisConverter ; 
 TYPE_1__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 TYPE_1__* PyArray_DescrNew (TYPE_1__*) ; 
 scalar_t__ PyArray_FromAny (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_Return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_SelectkindConverter ; 
 int /*<<< orphan*/  PyDataType_HASFIELDS (TYPE_1__*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyImport_ImportModule (char*) ; 
 int /*<<< orphan*/ * PyObject_CallMethod (int /*<<< orphan*/ *,char*,char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_XDECREF (TYPE_1__*) ; 

__attribute__((used)) static PyObject *
array_argpartition(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    int axis = -1;
    NPY_SELECTKIND sortkind = NPY_INTROSELECT;
    PyObject *order = NULL, *res;
    PyArray_Descr *newd, *saved=NULL;
    static char *kwlist[] = {"kth", "axis", "kind", "order", NULL};
    PyObject * kthobj;
    PyArrayObject * ktharray;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|O&O&O:argpartition", kwlist,
                                     &kthobj,
                                     PyArray_AxisConverter, &axis,
                                     PyArray_SelectkindConverter, &sortkind,
                                     &order)) {
        return NULL;
    }
    if (order == Py_None) {
        order = NULL;
    }
    if (order != NULL) {
        PyObject *new_name;
        PyObject *_numpy_internal;
        saved = PyArray_DESCR(self);
        if (!PyDataType_HASFIELDS(saved)) {
            PyErr_SetString(PyExc_ValueError, "Cannot specify "
                            "order when the array has no fields.");
            return NULL;
        }
        _numpy_internal = PyImport_ImportModule("numpy.core._internal");
        if (_numpy_internal == NULL) {
            return NULL;
        }
        new_name = PyObject_CallMethod(_numpy_internal, "_newnames",
                                       "OO", saved, order);
        Py_DECREF(_numpy_internal);
        if (new_name == NULL) {
            return NULL;
        }
        newd = PyArray_DescrNew(saved);
        Py_DECREF(newd->names);
        newd->names = new_name;
        ((PyArrayObject_fields *)self)->descr = newd;
    }

    ktharray = (PyArrayObject *)PyArray_FromAny(kthobj, NULL, 0, 1,
                                                NPY_ARRAY_DEFAULT, NULL);
    if (ktharray == NULL)
        return NULL;

    res = PyArray_ArgPartition(self, ktharray, axis, sortkind);
    Py_DECREF(ktharray);

    if (order != NULL) {
        Py_XDECREF(PyArray_DESCR(self));
        ((PyArrayObject_fields *)self)->descr = saved;
    }
    return PyArray_Return((PyArrayObject *)res);
}