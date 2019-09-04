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
 int /*<<< orphan*/  arch_irq_work_has_interrupt () ; 
 int /*<<< orphan*/  irq_work_run_list (struct llist_head*) ; 
 int /*<<< orphan*/  lazy_list ; 
 int /*<<< orphan*/  llist_empty (struct llist_head*) ; 
 int /*<<< orphan*/  raised_list ; 
 struct llist_head* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void irq_work_tick(void)
{
	struct llist_head *raised = this_cpu_ptr(&raised_list);

	if (!llist_empty(raised) && !arch_irq_work_has_interrupt())
		irq_work_run_list(raised);
	irq_work_run_list(this_cpu_ptr(&lazy_list));
}