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
struct irq_poll {int /*<<< orphan*/  list; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_POLL_F_DISABLE ; 
 int /*<<< orphan*/  IRQ_POLL_F_SCHED ; 
 int /*<<< orphan*/  IRQ_POLL_SOFTIRQ ; 
 int /*<<< orphan*/  blk_cpu_iopoll ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  raise_softirq_irqoff (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

void irq_poll_sched(struct irq_poll *iop)
{
	unsigned long flags;

	if (test_bit(IRQ_POLL_F_DISABLE, &iop->state))
		return;
	if (test_and_set_bit(IRQ_POLL_F_SCHED, &iop->state))
		return;

	local_irq_save(flags);
	list_add_tail(&iop->list, this_cpu_ptr(&blk_cpu_iopoll));
	raise_softirq_irqoff(IRQ_POLL_SOFTIRQ);
	local_irq_restore(flags);
}