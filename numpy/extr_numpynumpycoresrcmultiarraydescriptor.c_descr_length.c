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
struct TYPE_3__ {int /*<<< orphan*/  names; } ;
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 scalar_t__ PyDataType_HASFIELDS (TYPE_1__*) ; 
 int /*<<< orphan*/  PyTuple_GET_SIZE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Py_ssize_t
descr_length(PyObject *self0)
{
    PyArray_Descr *self = (PyArray_Descr *)self0;

    if (PyDataType_HASFIELDS(self)) {
        return PyTuple_GET_SIZE(self->names);
    }
    else {
        return 0;
    }
}