#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* subarray; } ;
struct TYPE_5__ {int /*<<< orphan*/ * shape; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyDataType_HASSUBARRAY (TYPE_2__*) ; 
 int /*<<< orphan*/  PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
arraydescr_shape_get(PyArray_Descr *self)
{
    if (!PyDataType_HASSUBARRAY(self)) {
        return PyTuple_New(0);
    }
    assert(PyTuple_Check(self->subarray->shape));
    Py_INCREF(self->subarray->shape);
    return self->subarray->shape;
}