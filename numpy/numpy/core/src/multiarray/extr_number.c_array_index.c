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
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_GETITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_ISINTEGER (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 

__attribute__((used)) static PyObject *
array_index(PyArrayObject *v)
{
    if (!PyArray_ISINTEGER(v) || PyArray_NDIM(v) != 0) {
        PyErr_SetString(PyExc_TypeError,
            "only integer scalar arrays can be converted to a scalar index");
        return NULL;
    }
    return PyArray_GETITEM(v, PyArray_DATA(v));
}