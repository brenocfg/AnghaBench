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
typedef  int /*<<< orphan*/  NPY_CLIPMODE ;

/* Variables and functions */
 int NPY_MAXDIMS ; 
 int /*<<< orphan*/  NPY_RAISE ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_AxisConverter ; 
 int /*<<< orphan*/  PyArray_ClipmodeConverter ; 
 int /*<<< orphan*/  PyArray_OutputConverter ; 
 int /*<<< orphan*/ * PyArray_Return (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_TakeFrom (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
array_take(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    int dimension = NPY_MAXDIMS;
    PyObject *indices;
    PyArrayObject *out = NULL;
    NPY_CLIPMODE mode = NPY_RAISE;
    static char *kwlist[] = {"indices", "axis", "out", "mode", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|O&O&O&:take", kwlist,
                                     &indices,
                                     PyArray_AxisConverter, &dimension,
                                     PyArray_OutputConverter, &out,
                                     PyArray_ClipmodeConverter, &mode))
        return NULL;

    return PyArray_Return((PyArrayObject *)
                PyArray_TakeFrom(self, indices, dimension, out, mode));
}