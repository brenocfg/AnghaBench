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
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  elsize; } ;
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 TYPE_1__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISEXTENDED (int /*<<< orphan*/ *) ; 
 int PyArray_NBYTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_free (char*) ; 
 char* PyArray_malloc (int) ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/ * PyUString_FromFormat (char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * PyUString_FromStringAndSize (char*,int) ; 
 scalar_t__ dump_data (char**,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_repr_builtin(PyArrayObject *self, int repr)
{
    PyObject *ret;
    char *string;
    /* max_n initial value is arbitrary, dump_data will extend it */
    Py_ssize_t n = 0, max_n = PyArray_NBYTES(self) * 4 + 7;

    if ((string = PyArray_malloc(max_n)) == NULL) {
        return PyErr_NoMemory();
    }

    if (dump_data(&string, &n, &max_n, PyArray_DATA(self),
                  PyArray_NDIM(self), PyArray_DIMS(self),
                  PyArray_STRIDES(self), self) < 0) {
        PyArray_free(string);
        return NULL;
    }

    if (repr) {
        if (PyArray_ISEXTENDED(self)) {
            ret = PyUString_FromFormat("array(%s, '%c%d')",
                                       string,
                                       PyArray_DESCR(self)->type,
                                       PyArray_DESCR(self)->elsize);
        }
        else {
            ret = PyUString_FromFormat("array(%s, '%c')",
                                       string,
                                       PyArray_DESCR(self)->type);
        }
    }
    else {
        ret = PyUString_FromStringAndSize(string, n);
    }

    PyArray_free(string);
    return ret;
}