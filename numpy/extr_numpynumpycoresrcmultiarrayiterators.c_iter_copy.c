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
struct TYPE_3__ {int /*<<< orphan*/  ao; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PyArray_Flatten (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
iter_copy(PyArrayIterObject *it, PyObject *args)
{
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }
    return PyArray_Flatten(it->ao, 0);
}