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
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int PyArray_PyIntAsIntp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_Occurred () ; 

__attribute__((used)) static int
coerce_index(PyObject *o, npy_intp *v)
{
    *v = PyArray_PyIntAsIntp(o);

    if ((*v) == -1 && PyErr_Occurred()) {
        PyErr_Clear();
        return 0;
    }
    return 1;
}