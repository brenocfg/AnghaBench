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
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 char NPY_SWAP ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyArray_ByteorderConverter ; 
 int /*<<< orphan*/  PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_DescrNewByteorder (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/ * PyArray_View (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_newbyteorder(PyArrayObject *self, PyObject *args)
{
    char endian = NPY_SWAP;
    PyArray_Descr *new;

    if (!PyArg_ParseTuple(args, "|O&:newbyteorder", PyArray_ByteorderConverter,
                          &endian)) {
        return NULL;
    }
    new = PyArray_DescrNewByteorder(PyArray_DESCR(self), endian);
    if (!new) {
        return NULL;
    }
    return PyArray_View(self, new, NULL);

}