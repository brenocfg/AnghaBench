#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * nested_child; int /*<<< orphan*/ * iter; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  NpyIter_Deallocate (int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_WarnEx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  PyErr_WriteUnraisable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_RuntimeWarning ; 
 int /*<<< orphan*/ * PyUString_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 TYPE_3__* Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ npyiter_has_writeback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
npyiter_dealloc(NewNpyArrayIterObject *self)
{
    if (self->iter) {
        if (npyiter_has_writeback(self->iter)) {
            if (PyErr_WarnEx(PyExc_RuntimeWarning,
                    "Temporary data has not been written back to one of the "
                    "operands. Typically nditer is used as a context manager "
                    "otherwise 'close' must be called before reading iteration "
                    "results.", 1) < 0) {
                PyObject *s;

                s = PyUString_FromString("npyiter_dealloc");
                if (s) {
                    PyErr_WriteUnraisable(s);
                    Py_DECREF(s);
                }
                else {
                    PyErr_WriteUnraisable(Py_None);
                }
            }
        }
        NpyIter_Deallocate(self->iter);
        self->iter = NULL;
        Py_XDECREF(self->nested_child);
        self->nested_child = NULL;
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}