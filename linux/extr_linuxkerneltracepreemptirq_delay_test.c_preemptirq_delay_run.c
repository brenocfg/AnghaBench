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

/* Variables and functions */
 int /*<<< orphan*/  busy_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_mode ; 

__attribute__((used)) static int preemptirq_delay_run(void *data)
{
	unsigned long flags;

	if (!strcmp(test_mode, "irq")) {
		local_irq_save(flags);
		busy_wait(delay);
		local_irq_restore(flags);
	} else if (!strcmp(test_mode, "preempt")) {
		preempt_disable();
		busy_wait(delay);
		preempt_enable();
	}

	return 0;
}