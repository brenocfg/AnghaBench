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
struct TYPE_3__ {int flags; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 int NPY_ALIGNED_STRUCT ; 
 int /*<<< orphan*/ * Py_False ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_True ; 

__attribute__((used)) static PyObject *
arraydescr_isalignedstruct_get(PyArray_Descr *self)
{
    PyObject *ret;
    ret = (self->flags&NPY_ALIGNED_STRUCT) ? Py_True : Py_False;
    Py_INCREF(ret);
    return ret;
}