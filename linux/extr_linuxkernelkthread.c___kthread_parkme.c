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
struct kthread {int /*<<< orphan*/  parked; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTHREAD_SHOULD_PARK ; 
 int /*<<< orphan*/  TASK_PARKED ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_special_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __kthread_parkme(struct kthread *self)
{
	for (;;) {
		/*
		 * TASK_PARKED is a special state; we must serialize against
		 * possible pending wakeups to avoid store-store collisions on
		 * task->state.
		 *
		 * Such a collision might possibly result in the task state
		 * changin from TASK_PARKED and us failing the
		 * wait_task_inactive() in kthread_park().
		 */
		set_special_state(TASK_PARKED);
		if (!test_bit(KTHREAD_SHOULD_PARK, &self->flags))
			break;

		complete(&self->parked);
		schedule();
	}
	__set_current_state(TASK_RUNNING);
}