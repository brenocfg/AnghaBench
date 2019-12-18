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
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;
struct irq_desc {scalar_t__ action; TYPE_1__ irq_data; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ irq_poll_cpu ; 
 int /*<<< orphan*/  irqd_irq_disabled (TYPE_1__*) ; 
 scalar_t__ irqd_irq_inprogress (TYPE_1__*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ smp_processor_id () ; 

bool irq_wait_for_poll(struct irq_desc *desc)
{
	if (WARN_ONCE(irq_poll_cpu == smp_processor_id(),
		      "irq poll in progress on cpu %d for irq %d\n",
		      smp_processor_id(), desc->irq_data.irq))
		return false;

#ifdef CONFIG_SMP
	do {
		raw_spin_unlock(&desc->lock);
		while (irqd_irq_inprogress(&desc->irq_data))
			cpu_relax();
		raw_spin_lock(&desc->lock);
	} while (irqd_irq_inprogress(&desc->irq_data));
	/* Might have been disabled in meantime */
	return !irqd_irq_disabled(&desc->irq_data) && desc->action;
#else
	return false;
#endif
}