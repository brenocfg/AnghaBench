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
struct TYPE_4__ {int /*<<< orphan*/  base; int /*<<< orphan*/  shape; } ;
typedef  TYPE_1__ PyArray_ArrayDescr ;

/* Variables and functions */
 int PyArray_EquivTypes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_Occurred () ; 
 int PyObject_RichCompareBool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_EQ ; 

__attribute__((used)) static int
_equivalent_subarrays(PyArray_ArrayDescr *sub1, PyArray_ArrayDescr *sub2)
{
    int val;

    if (sub1 == sub2) {
        return 1;

    }
    if (sub1 == NULL || sub2 == NULL) {
        return 0;
    }

    val = PyObject_RichCompareBool(sub1->shape, sub2->shape, Py_EQ);
    if (val != 1 || PyErr_Occurred()) {
        PyErr_Clear();
        return 0;
    }

    return PyArray_EquivTypes(sub1->base, sub2->base);
}