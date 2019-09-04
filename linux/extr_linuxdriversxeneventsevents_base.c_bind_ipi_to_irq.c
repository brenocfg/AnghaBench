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
struct irq_info {scalar_t__ type; } ;
struct evtchn_bind_ipi {int port; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EVTCHNOP_bind_ipi ; 
 scalar_t__ HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_ipi*) ; 
 scalar_t__ IRQT_IPI ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __unbind_from_irq (int) ; 
 int /*<<< orphan*/  bind_evtchn_to_cpu (int,unsigned int) ; 
 int /*<<< orphan*/  handle_percpu_irq ; 
 struct irq_info* info_for_irq (int) ; 
 int /*<<< orphan*/  ipi_to_irq ; 
 int /*<<< orphan*/  irq_mapping_update_lock ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int xen_allocate_irq_dynamic () ; 
 int xen_irq_info_ipi_setup (unsigned int,int,int,unsigned int) ; 
 int /*<<< orphan*/  xen_percpu_chip ; 
 int /*<<< orphan*/  xen_vcpu_nr (unsigned int) ; 

__attribute__((used)) static int bind_ipi_to_irq(unsigned int ipi, unsigned int cpu)
{
	struct evtchn_bind_ipi bind_ipi;
	int evtchn, irq;
	int ret;

	mutex_lock(&irq_mapping_update_lock);

	irq = per_cpu(ipi_to_irq, cpu)[ipi];

	if (irq == -1) {
		irq = xen_allocate_irq_dynamic();
		if (irq < 0)
			goto out;

		irq_set_chip_and_handler_name(irq, &xen_percpu_chip,
					      handle_percpu_irq, "ipi");

		bind_ipi.vcpu = xen_vcpu_nr(cpu);
		if (HYPERVISOR_event_channel_op(EVTCHNOP_bind_ipi,
						&bind_ipi) != 0)
			BUG();
		evtchn = bind_ipi.port;

		ret = xen_irq_info_ipi_setup(cpu, irq, evtchn, ipi);
		if (ret < 0) {
			__unbind_from_irq(irq);
			irq = ret;
			goto out;
		}
		bind_evtchn_to_cpu(evtchn, cpu);
	} else {
		struct irq_info *info = info_for_irq(irq);
		WARN_ON(info == NULL || info->type != IRQT_IPI);
	}

 out:
	mutex_unlock(&irq_mapping_update_lock);
	return irq;
}