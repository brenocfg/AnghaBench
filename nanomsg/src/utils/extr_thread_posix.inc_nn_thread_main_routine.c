#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nn_thread {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* routine ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *nn_thread_main_routine (void *arg)
{
    struct nn_thread *self;

    self = (struct nn_thread*) arg;

    /*  Run the thread routine. */
    self->routine (self->arg);
    return NULL;
}