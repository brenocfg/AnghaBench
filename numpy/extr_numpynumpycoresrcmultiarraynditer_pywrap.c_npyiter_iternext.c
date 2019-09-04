#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int finished; int /*<<< orphan*/ * iter; scalar_t__ (* iternext ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 scalar_t__ NPY_SUCCEED ; 
 int /*<<< orphan*/  Py_RETURN_FALSE ; 
 int /*<<< orphan*/  Py_RETURN_TRUE ; 
 scalar_t__ npyiter_resetbasepointers (TYPE_1__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
npyiter_iternext(NewNpyArrayIterObject *self)
{
    if (self->iter != NULL && self->iternext != NULL &&
                        !self->finished && self->iternext(self->iter)) {
        /* If there is nesting, the nested iterators should be reset */
        if (npyiter_resetbasepointers(self) != NPY_SUCCEED) {
            return NULL;
        }

        Py_RETURN_TRUE;
    }
    else {
        self->finished = 1;
        Py_RETURN_FALSE;
    }
}