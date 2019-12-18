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
struct irq_work {int /*<<< orphan*/  llnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __irq_work_queue_local (struct irq_work*) ; 
 int /*<<< orphan*/  arch_send_call_function_single_ipi (int) ; 
 int /*<<< orphan*/  cpu_is_offline (int) ; 
 int /*<<< orphan*/  in_nmi () ; 
 int /*<<< orphan*/  irq_work_claim (struct irq_work*) ; 
 int irq_work_queue (struct irq_work*) ; 
 scalar_t__ llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  raised_list ; 
 int smp_processor_id () ; 

bool irq_work_queue_on(struct irq_work *work, int cpu)
{
#ifndef CONFIG_SMP
	return irq_work_queue(work);

#else /* CONFIG_SMP: */
	/* All work should have been flushed before going offline */
	WARN_ON_ONCE(cpu_is_offline(cpu));

	/* Only queue if not already pending */
	if (!irq_work_claim(work))
		return false;

	preempt_disable();
	if (cpu != smp_processor_id()) {
		/* Arch remote IPI send/receive backend aren't NMI safe */
		WARN_ON_ONCE(in_nmi());
		if (llist_add(&work->llnode, &per_cpu(raised_list, cpu)))
			arch_send_call_function_single_ipi(cpu);
	} else {
		__irq_work_queue_local(work);
	}
	preempt_enable();

	return true;
#endif /* CONFIG_SMP */
}