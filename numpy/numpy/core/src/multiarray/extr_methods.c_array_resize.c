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
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Dims ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ANYORDER ; 
 int /*<<< orphan*/  NpyArg_ParseKeywords (int /*<<< orphan*/ *,char*,char**,int*) ; 
 int /*<<< orphan*/  PyArray_IntpConverter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_Resize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PyTuple_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  npy_free_cache_dim_obj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
array_resize(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"refcheck", NULL};
    Py_ssize_t size = PyTuple_Size(args);
    int refcheck = 1;
    PyArray_Dims newshape;
    PyObject *ret, *obj;


    if (!NpyArg_ParseKeywords(kwds, "|i", kwlist,  &refcheck)) {
        return NULL;
    }

    if (size == 0) {
        Py_RETURN_NONE;
    }
    else if (size == 1) {
        obj = PyTuple_GET_ITEM(args, 0);
        if (obj == Py_None) {
            Py_RETURN_NONE;
        }
        args = obj;
    }
    if (!PyArray_IntpConverter(args, &newshape)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "invalid shape");
        }
        return NULL;
    }

    ret = PyArray_Resize(self, &newshape, refcheck, NPY_ANYORDER);
    npy_free_cache_dim_obj(newshape);
    if (ret == NULL) {
        return NULL;
    }
    Py_DECREF(ret);
    Py_RETURN_NONE;
}