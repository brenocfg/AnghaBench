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
typedef  int /*<<< orphan*/  PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ NPY_FAIL ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ PyArray_DescrConverter (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/ * PyArray_View (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 scalar_t__ PyType_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyType_IsSubtype (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_view(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *out_dtype = NULL;
    PyObject *out_type = NULL;
    PyArray_Descr *dtype = NULL;

    static char *kwlist[] = {"dtype", "type", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OO:view", kwlist,
                                     &out_dtype,
                                     &out_type)) {
        return NULL;
    }

    /* If user specified a positional argument, guess whether it
       represents a type or a dtype for backward compatibility. */
    if (out_dtype) {
        /* type specified? */
        if (PyType_Check(out_dtype) &&
            PyType_IsSubtype((PyTypeObject *)out_dtype,
                             &PyArray_Type)) {
            if (out_type) {
                PyErr_SetString(PyExc_ValueError,
                                "Cannot specify output type twice.");
                return NULL;
            }
            out_type = out_dtype;
            out_dtype = NULL;
        }
    }

    if ((out_type) && (!PyType_Check(out_type) ||
                       !PyType_IsSubtype((PyTypeObject *)out_type,
                                         &PyArray_Type))) {
        PyErr_SetString(PyExc_ValueError,
                        "Type must be a sub-type of ndarray type");
        return NULL;
    }

    if ((out_dtype) &&
        (PyArray_DescrConverter(out_dtype, &dtype) == NPY_FAIL)) {
        return NULL;
    }

    return PyArray_View(self, dtype, (PyTypeObject*)out_type);
}