#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* subarray; } ;
struct TYPE_6__ {TYPE_2__* base; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyDataType_HASSUBARRAY (TYPE_2__*) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_2__*) ; 

__attribute__((used)) static PyObject *
arraydescr_base_get(PyArray_Descr *self)
{
    if (!PyDataType_HASSUBARRAY(self)) {
        Py_INCREF(self);
        return (PyObject *)self;
    }
    Py_INCREF(self->subarray->base);
    return (PyObject *)(self->subarray->base);
}