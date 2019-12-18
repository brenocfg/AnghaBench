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
struct TYPE_3__ {int started; int finished; int /*<<< orphan*/  iter; struct TYPE_3__* nested_child; int /*<<< orphan*/  dataptrs; } ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 int NPY_FAIL ; 
 scalar_t__ NPY_SUCCEED ; 
 scalar_t__ NpyIter_GetIterSize (int /*<<< orphan*/ ) ; 
 scalar_t__ NpyIter_ResetBasePointers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
npyiter_resetbasepointers(NewNpyArrayIterObject *self)
{
    while (self->nested_child) {
        if (NpyIter_ResetBasePointers(self->nested_child->iter,
                                        self->dataptrs, NULL) != NPY_SUCCEED) {
            return NPY_FAIL;
        }
        self = self->nested_child;
        if (NpyIter_GetIterSize(self->iter) == 0) {
            self->started = 1;
            self->finished = 1;
        }
        else {
            self->started = 0;
            self->finished = 0;
        }
    }

    return NPY_SUCCEED;
}