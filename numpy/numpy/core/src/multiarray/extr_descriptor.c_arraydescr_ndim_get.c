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
struct TYPE_5__ {int /*<<< orphan*/  shape; } ;
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyDataType_HASSUBARRAY (TYPE_2__*) ; 
 int /*<<< orphan*/ * PyInt_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_Size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
arraydescr_ndim_get(PyArray_Descr *self)
{
    Py_ssize_t ndim;

    if (!PyDataType_HASSUBARRAY(self)) {
        return PyInt_FromLong(0);
    }

    /*
     * PyTuple_Size has built in check
     * for tuple argument
     */
    ndim = PyTuple_Size(self->subarray->shape);
    return PyInt_FromLong(ndim);
}