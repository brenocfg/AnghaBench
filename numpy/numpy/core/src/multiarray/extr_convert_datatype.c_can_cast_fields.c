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
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  NPY_CASTING ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_CanCastTypeTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyDict_GetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyDict_Next (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ PyDict_Size (int /*<<< orphan*/ *) ; 
 scalar_t__ PyTuple_GET_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
can_cast_fields(PyObject *field1, PyObject *field2, NPY_CASTING casting)
{
    Py_ssize_t ppos;
    PyObject *key;
    PyObject *tuple1, *tuple2;

    if (field1 == field2) {
        return 1;
    }
    if (field1 == NULL || field2 == NULL) {
        return 0;
    }
    if (PyDict_Size(field1) != PyDict_Size(field2)) {
        return 0;
    }

    /* Iterate over all the fields and compare for castability */
    ppos = 0;
    while (PyDict_Next(field1, &ppos, &key, &tuple1)) {
        if ((tuple2 = PyDict_GetItem(field2, key)) == NULL) {
            return 0;
        }
        /* Compare the dtype of the field for castability */
        if (!PyArray_CanCastTypeTo(
                        (PyArray_Descr *)PyTuple_GET_ITEM(tuple1, 0),
                        (PyArray_Descr *)PyTuple_GET_ITEM(tuple2, 0),
                        casting)) {
            return 0;
        }
    }

    return 1;
}