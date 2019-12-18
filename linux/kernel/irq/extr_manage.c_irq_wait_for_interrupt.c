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
struct irqaction {int /*<<< orphan*/  thread_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQTF_RUNTHREAD ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int irq_wait_for_interrupt(struct irqaction *action)
{
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);

		if (kthread_should_stop()) {
			/* may need to run one last time */
			if (test_and_clear_bit(IRQTF_RUNTHREAD,
					       &action->thread_flags)) {
				__set_current_state(TASK_RUNNING);
				return 0;
			}
			__set_current_state(TASK_RUNNING);
			return -1;
		}

		if (test_and_clear_bit(IRQTF_RUNTHREAD,
				       &action->thread_flags)) {
			__set_current_state(TASK_RUNNING);
			return 0;
		}
		schedule();
	}
}