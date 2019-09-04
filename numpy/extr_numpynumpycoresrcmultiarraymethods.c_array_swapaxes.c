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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int*,int*) ; 
 int /*<<< orphan*/ * PyArray_SwapAxes (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static PyObject *
array_swapaxes(PyArrayObject *self, PyObject *args)
{
    int axis1, axis2;

    if (!PyArg_ParseTuple(args, "ii:swapaxes", &axis1, &axis2)) {
        return NULL;
    }
    return PyArray_SwapAxes(self, axis1, axis2);
}