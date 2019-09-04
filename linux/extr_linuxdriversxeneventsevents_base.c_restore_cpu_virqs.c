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
struct evtchn_bind_virq {int virq; int port; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EVTCHNOP_bind_virq ; 
 scalar_t__ HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_virq*) ; 
 int NR_VIRQS ; 
 int /*<<< orphan*/  bind_evtchn_to_cpu (int,unsigned int) ; 
 int* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int virq_from_irq (int) ; 
 int /*<<< orphan*/  virq_to_irq ; 
 int /*<<< orphan*/  xen_irq_info_virq_setup (unsigned int,int,int,int) ; 
 int /*<<< orphan*/  xen_vcpu_nr (unsigned int) ; 

__attribute__((used)) static void restore_cpu_virqs(unsigned int cpu)
{
	struct evtchn_bind_virq bind_virq;
	int virq, irq, evtchn;

	for (virq = 0; virq < NR_VIRQS; virq++) {
		if ((irq = per_cpu(virq_to_irq, cpu)[virq]) == -1)
			continue;

		BUG_ON(virq_from_irq(irq) != virq);

		/* Get a new binding from Xen. */
		bind_virq.virq = virq;
		bind_virq.vcpu = xen_vcpu_nr(cpu);
		if (HYPERVISOR_event_channel_op(EVTCHNOP_bind_virq,
						&bind_virq) != 0)
			BUG();
		evtchn = bind_virq.port;

		/* Record the new mapping. */
		(void)xen_irq_info_virq_setup(cpu, irq, evtchn, virq);
		bind_evtchn_to_cpu(evtchn, cpu);
	}
}