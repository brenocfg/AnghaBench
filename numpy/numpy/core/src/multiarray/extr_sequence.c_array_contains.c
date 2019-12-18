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
 int /*<<< orphan*/  NPY_MAXDIMS ; 
 int /*<<< orphan*/ * PyArray_Any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_EnsureAnyArray (int /*<<< orphan*/ ) ; 
 int PyObject_IsTrue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyObject_RichCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_EQ ; 

__attribute__((used)) static int
array_contains(PyArrayObject *self, PyObject *el)
{
    /* equivalent to (self == el).any() */

    int ret;
    PyObject *res, *any;

    res = PyArray_EnsureAnyArray(PyObject_RichCompare((PyObject *)self,
                                                      el, Py_EQ));
    if (res == NULL) {
        return -1;
    }
    any = PyArray_Any((PyArrayObject *)res, NPY_MAXDIMS, NULL);
    Py_DECREF(res);
    ret = PyObject_IsTrue(any);
    Py_DECREF(any);
    return ret;
}