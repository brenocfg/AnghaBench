#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayObject_fields ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ IsAligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NPY_ARRAY_ALIGNED ; 
 int /*<<< orphan*/  NPY_ARRAY_UPDATEIFCOPY ; 
 int /*<<< orphan*/  NPY_ARRAY_WRITEABLE ; 
 int /*<<< orphan*/  NPY_ARRAY_WRITEBACKIFCOPY ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyArray_CLEARFLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_ENABLEFLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 scalar_t__ PyObject_IsTrue (int /*<<< orphan*/ *) ; 
 scalar_t__ PyObject_Not (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ _IsWriteable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_setflags(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"write", "align", "uic", NULL};
    PyObject *write_flag = Py_None;
    PyObject *align_flag = Py_None;
    PyObject *uic = Py_None;
    int flagback = PyArray_FLAGS(self);

    PyArrayObject_fields *fa = (PyArrayObject_fields *)self;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOO:setflags", kwlist,
                                     &write_flag,
                                     &align_flag,
                                     &uic))
        return NULL;

    if (align_flag != Py_None) {
        if (PyObject_Not(align_flag)) {
            PyArray_CLEARFLAGS(self, NPY_ARRAY_ALIGNED);
        }
        else if (IsAligned(self)) {
            PyArray_ENABLEFLAGS(self, NPY_ARRAY_ALIGNED);
        }
        else {
            PyErr_SetString(PyExc_ValueError,
                            "cannot set aligned flag of mis-"
                            "aligned array to True");
            return NULL;
        }
    }

    if (uic != Py_None) {
        if (PyObject_IsTrue(uic)) {
            fa->flags = flagback;
            PyErr_SetString(PyExc_ValueError,
                            "cannot set WRITEBACKIFCOPY "
                            "flag to True");
            return NULL;
        }
        else {
            PyArray_CLEARFLAGS(self, NPY_ARRAY_WRITEBACKIFCOPY);
            PyArray_CLEARFLAGS(self, NPY_ARRAY_UPDATEIFCOPY);
            Py_XDECREF(fa->base);
            fa->base = NULL;
        }
    }

    if (write_flag != Py_None) {
        if (PyObject_IsTrue(write_flag)) {
            if (_IsWriteable(self)) {
                PyArray_ENABLEFLAGS(self, NPY_ARRAY_WRITEABLE);
            }
            else {
                fa->flags = flagback;
                PyErr_SetString(PyExc_ValueError,
                                "cannot set WRITEABLE "
                                "flag to True of this "
                                "array");
                return NULL;
            }
        }
        else {
            PyArray_CLEARFLAGS(self, NPY_ARRAY_WRITEABLE);
        }
    }

    Py_RETURN_NONE;
}