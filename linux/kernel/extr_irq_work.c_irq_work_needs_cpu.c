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
struct llist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ arch_irq_work_has_interrupt () ; 
 int /*<<< orphan*/  cpu_is_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lazy_list ; 
 scalar_t__ llist_empty (struct llist_head*) ; 
 int /*<<< orphan*/  raised_list ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct llist_head* this_cpu_ptr (int /*<<< orphan*/ *) ; 

bool irq_work_needs_cpu(void)
{
	struct llist_head *raised, *lazy;

	raised = this_cpu_ptr(&raised_list);
	lazy = this_cpu_ptr(&lazy_list);

	if (llist_empty(raised) || arch_irq_work_has_interrupt())
		if (llist_empty(lazy))
			return false;

	/* All work should have been flushed before going offline */
	WARN_ON_ONCE(cpu_is_offline(smp_processor_id()));

	return true;
}