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
struct irq_info {scalar_t__ type; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IRQT_UNBOUND ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  bind_evtchn_to_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int get_evtchn_to_irq (int) ; 
 struct irq_info* info_for_irq (int) ; 
 int /*<<< orphan*/  irq_mapping_update_lock ; 
 int /*<<< orphan*/  irq_set_affinity (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_irq_info_evtchn_setup (int,int) ; 

void rebind_evtchn_irq(int evtchn, int irq)
{
	struct irq_info *info = info_for_irq(irq);

	if (WARN_ON(!info))
		return;

	/* Make sure the irq is masked, since the new event channel
	   will also be masked. */
	disable_irq(irq);

	mutex_lock(&irq_mapping_update_lock);

	/* After resume the irq<->evtchn mappings are all cleared out */
	BUG_ON(get_evtchn_to_irq(evtchn) != -1);
	/* Expect irq to have been bound before,
	   so there should be a proper type */
	BUG_ON(info->type == IRQT_UNBOUND);

	(void)xen_irq_info_evtchn_setup(irq, evtchn);

	mutex_unlock(&irq_mapping_update_lock);

        bind_evtchn_to_cpu(evtchn, info->cpu);
	/* This will be deferred until interrupt is processed */
	irq_set_affinity(irq, cpumask_of(info->cpu));

	/* Unmask the event channel. */
	enable_irq(irq);
}