#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char kind; int /*<<< orphan*/  fields; int /*<<< orphan*/ * names; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 scalar_t__ PyDataType_HASFIELDS (TYPE_1__*) ; 
 int /*<<< orphan*/  PyDataType_REFCHK (TYPE_1__*) ; 
 int /*<<< orphan*/ * PyDict_GetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
invalid_union_object_dtype(PyArray_Descr *new, PyArray_Descr *conv)
{
    PyObject *name, *tup;
    PyArray_Descr *dtype;

    if (!PyDataType_REFCHK(new) && !PyDataType_REFCHK(conv)) {
        return 0;
    }
    if (PyDataType_HASFIELDS(new) || new->kind != 'O') {
        goto fail;
    }
    if (!PyDataType_HASFIELDS(conv) || PyTuple_GET_SIZE(conv->names) != 1) {
        goto fail;
    }
    name = PyTuple_GET_ITEM(conv->names, 0);
    if (name == NULL) {
        return -1;
    }
    tup = PyDict_GetItem(conv->fields, name);
    if (tup == NULL) {
        return -1;
    }
    dtype = (PyArray_Descr *)PyTuple_GET_ITEM(tup, 0);
    if (dtype == NULL) {
        return -1;
    }
    if (dtype->kind != 'O') {
        goto fail;
    }
    return 0;

fail:
    PyErr_SetString(PyExc_ValueError,
            "dtypes of the form (old_dtype, new_dtype) containing the object "
            "dtype are not supported");
    return -1;
}