#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  names; } ;
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _subscript_by_name (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
_subscript_by_index(PyArray_Descr *self, Py_ssize_t i)
{
    PyObject *name = PySequence_GetItem(self->names, i);
    PyObject *ret;
    if (name == NULL) {
        PyErr_Format(PyExc_IndexError,
                     "Field index %zd out of range.", i);
        return NULL;
    }
    ret = _subscript_by_name(self, name);
    Py_DECREF(name);
    return ret;
}