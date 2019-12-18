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
 int NPY_ARRAY_WRITEABLE ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 int PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyLong_FromVoidPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_False ; 
 int /*<<< orphan*/  Py_True ; 

__attribute__((used)) static PyObject *
array_dataptr_get(PyArrayObject *self)
{
    return Py_BuildValue("NO",
                         PyLong_FromVoidPtr(PyArray_DATA(self)),
                         (PyArray_FLAGS(self) & NPY_ARRAY_WRITEABLE ? Py_False :
                          Py_True));
}