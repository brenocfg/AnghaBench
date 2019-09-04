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
struct TYPE_4__ {int /*<<< orphan*/ * names; int /*<<< orphan*/ * fields; } ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_Occurred () ; 
 int PyObject_RichCompareBool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_EQ ; 

__attribute__((used)) static int
_equivalent_fields(PyArray_Descr *type1, PyArray_Descr *type2) {

    int val;

    if (type1->fields == type2->fields && type1->names == type2->names) {
        return 1;
    }
    if (type1->fields == NULL || type2->fields == NULL) {
        return 0;
    }

    val = PyObject_RichCompareBool(type1->fields, type2->fields, Py_EQ);
    if (val != 1 || PyErr_Occurred()) {
        PyErr_Clear();
        return 0;
    }

    val = PyObject_RichCompareBool(type1->names, type2->names, Py_EQ);
    if (val != 1 || PyErr_Occurred()) {
        PyErr_Clear();
        return 0;
    }

    return 1;
}