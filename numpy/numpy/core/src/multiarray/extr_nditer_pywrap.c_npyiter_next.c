#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int finished; int started; int /*<<< orphan*/ * iter; int /*<<< orphan*/  (* iternext ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 scalar_t__ NPY_SUCCEED ; 
 scalar_t__ npyiter_resetbasepointers (TYPE_1__*) ; 
 int /*<<< orphan*/ * npyiter_value_get (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
npyiter_next(NewNpyArrayIterObject *self)
{
    if (self->iter == NULL || self->iternext == NULL ||
                self->finished) {
        return NULL;
    }

    /*
     * Use the started flag for the Python iteration protocol to work
     * when buffering is enabled.
     */
    if (self->started) {
        if (!self->iternext(self->iter)) {
            self->finished = 1;
            return NULL;
        }

        /* If there is nesting, the nested iterators should be reset */
        if (npyiter_resetbasepointers(self) != NPY_SUCCEED) {
            return NULL;
        }
    }
    self->started = 1;

    return npyiter_value_get(self);
}