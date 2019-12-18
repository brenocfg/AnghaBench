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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * PyArray_Conjugate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_OutputConverter ; 

__attribute__((used)) static PyObject *
array_conjugate(PyArrayObject *self, PyObject *args)
{
    PyArrayObject *out = NULL;
    if (!PyArg_ParseTuple(args, "|O&:conjugate",
                          PyArray_OutputConverter,
                          &out)) {
        return NULL;
    }
    return PyArray_Conjugate(self, out);
}