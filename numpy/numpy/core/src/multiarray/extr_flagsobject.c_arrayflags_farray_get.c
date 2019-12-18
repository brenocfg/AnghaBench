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
typedef  TYPE_1__ PyArrayFlagsObject ;

/* Variables and functions */
 int NPY_ARRAY_ALIGNED ; 
 int NPY_ARRAY_C_CONTIGUOUS ; 
 int NPY_ARRAY_F_CONTIGUOUS ; 
 int NPY_ARRAY_WRITEABLE ; 
 int /*<<< orphan*/ * Py_False ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_True ; 

__attribute__((used)) static PyObject *
arrayflags_farray_get(PyArrayFlagsObject *self)
{
    PyObject *item;

    if (((self->flags & (NPY_ARRAY_ALIGNED|
                         NPY_ARRAY_WRITEABLE|
                         NPY_ARRAY_F_CONTIGUOUS)) != 0) &&
        !((self->flags & NPY_ARRAY_C_CONTIGUOUS) != 0)) {
        item = Py_True;
    }
    else {
        item = Py_False;
    }
    Py_INCREF(item);
    return item;
}