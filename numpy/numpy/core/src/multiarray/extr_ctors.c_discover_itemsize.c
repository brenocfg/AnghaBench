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
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_STRING ; 
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 int PyArray_ITEMSIZE (int /*<<< orphan*/ *) ; 
 int PyArray_MAX (int,int) ; 
 scalar_t__ PyBuffer_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyMemoryView_Check (int /*<<< orphan*/ *) ; 
 int PyObject_Length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_Str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_Unicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,int) ; 
 int PySequence_Length (int /*<<< orphan*/ *) ; 
 scalar_t__ PyString_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
discover_itemsize(PyObject *s, int nd, int *itemsize, int string_type)
{
    int r;
    npy_intp n, i;

    if (PyArray_Check(s)) {
        *itemsize = PyArray_MAX(*itemsize, PyArray_ITEMSIZE((PyArrayObject *)s));
        return 0;
    }

    if ((nd == 0) || PyString_Check(s) ||
#if defined(NPY_PY3K)
            PyMemoryView_Check(s) ||
#else
            PyBuffer_Check(s) ||
#endif
            PyUnicode_Check(s)) {

        /* If an object has no length, leave it be */
        if (string_type && s != NULL &&
                !PyString_Check(s) && !PyUnicode_Check(s)) {
            PyObject *s_string = NULL;
            if (string_type == NPY_STRING) {
                s_string = PyObject_Str(s);
            }
            else {
#if defined(NPY_PY3K)
                s_string = PyObject_Str(s);
#else
                s_string = PyObject_Unicode(s);
#endif
            }
            if (s_string) {
                n = PyObject_Length(s_string);
                Py_DECREF(s_string);
            }
            else {
                n = -1;
            }
        }
        else {
            n = PyObject_Length(s);
        }
        if (n == -1) {
            PyErr_Clear();
        }
        else {
            *itemsize = PyArray_MAX(*itemsize, n);
        }
        return 0;
    }

    n = PySequence_Length(s);
    for (i = 0; i < n; i++) {
        PyObject *e = PySequence_GetItem(s,i);

        if (e == NULL) {
            return -1;
        }

        r = discover_itemsize(e, nd - 1, itemsize, string_type);
        Py_DECREF(e);
        if (r == -1) {
            return -1;
        }
    }

    return 0;
}