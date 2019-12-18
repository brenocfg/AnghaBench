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
struct TYPE_5__ {int /*<<< orphan*/  shape; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyDataType_HASSUBARRAY (TYPE_2__*) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 

__attribute__((used)) static PyObject *
arraydescr_subdescr_get(PyArray_Descr *self)
{
    if (!PyDataType_HASSUBARRAY(self)) {
        Py_RETURN_NONE;
    }
    return Py_BuildValue("OO",
            (PyObject *)self->subarray->base, self->subarray->shape);
}