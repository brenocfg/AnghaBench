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
typedef  int /*<<< orphan*/  NPY_SEARCHSIDE ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_SEARCHLEFT ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * PyArray_Return (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SearchSorted (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_SearchsideConverter ; 
 int /*<<< orphan*/ * Py_None ; 

__attribute__((used)) static PyObject *
array_searchsorted(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"keys", "side", "sorter", NULL};
    PyObject *keys;
    PyObject *sorter;
    NPY_SEARCHSIDE side = NPY_SEARCHLEFT;

    sorter = NULL;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|O&O:searchsorted",
                                     kwlist, &keys,
                                     PyArray_SearchsideConverter, &side, &sorter)) {
        return NULL;
    }
    if (sorter == Py_None) {
        sorter = NULL;
    }
    return PyArray_Return((PyArrayObject *)PyArray_SearchSorted(self, keys, side, sorter));
}