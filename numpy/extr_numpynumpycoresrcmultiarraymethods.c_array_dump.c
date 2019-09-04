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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int PyArray_Dump (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 

__attribute__((used)) static PyObject *
array_dump(PyArrayObject *self, PyObject *args)
{
    PyObject *file = NULL;
    int ret;

    if (!PyArg_ParseTuple(args, "O:dump", &file)) {
        return NULL;
    }
    ret = PyArray_Dump((PyObject *)self, file, 2);
    if (ret < 0) {
        return NULL;
    }
    Py_RETURN_NONE;
}