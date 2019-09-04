#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Dims ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyUString_ConcatAndDel (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUString_FromFormat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert_shape_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
raise_reshape_size_mismatch(PyArray_Dims *newshape, PyArrayObject *arr)
{
    PyObject *msg = PyUString_FromFormat("cannot reshape array of size %zd "
                                         "into shape ", PyArray_SIZE(arr));
    PyObject *tmp = convert_shape_to_string(newshape->len, newshape->ptr, "");

    PyUString_ConcatAndDel(&msg, tmp);
    if (msg != NULL) {
        PyErr_SetObject(PyExc_ValueError, msg);
        Py_DECREF(msg);
    }
}