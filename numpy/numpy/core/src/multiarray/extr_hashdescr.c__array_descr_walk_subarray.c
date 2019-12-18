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
struct TYPE_3__ {int /*<<< orphan*/  base; int /*<<< orphan*/ * shape; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_ArrayDescr ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_SystemError ; 
 scalar_t__ PyInt_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyList_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GetItem (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PyTuple_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ ) ; 
 int _array_descr_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _array_descr_walk_subarray(PyArray_ArrayDescr* adescr, PyObject *l)
{
    PyObject *item;
    Py_ssize_t i;
    int st;

    /*
     * Add shape and descr itself to the list of object to hash
     */
    if (PyTuple_Check(adescr->shape)) {
        for(i = 0; i < PyTuple_Size(adescr->shape); ++i) {
            item = PyTuple_GetItem(adescr->shape, i);
            if (item == NULL) {
                PyErr_SetString(PyExc_SystemError,
                        "(Hash) Error while getting shape item of subarray dtype ???");
                return -1;
            }
            PyList_Append(l, item);
        }
    }
    else if (PyInt_Check(adescr->shape)) {
        PyList_Append(l, adescr->shape);
    }
    else {
        PyErr_SetString(PyExc_SystemError,
                "(Hash) Shape of subarray dtype neither a tuple or int ???");
        return -1;
    }

    Py_INCREF(adescr->base);
    st = _array_descr_walk(adescr->base, l);
    Py_DECREF(adescr->base);

    return st;
}