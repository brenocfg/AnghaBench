#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int irq; } ;
struct TYPE_5__ {TYPE_4__ its_vpe; } ;
struct TYPE_6__ {TYPE_1__ vgic_v3; } ;
struct TYPE_7__ {TYPE_2__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_3__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQCHIP_STATE_PENDING ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int irq_set_affinity (int,int /*<<< orphan*/ ) ; 
 int irq_set_irqchip_state (int,int /*<<< orphan*/ ,int) ; 
 int its_schedule_vpe (TYPE_4__*,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  vgic_supports_direct_msis (int /*<<< orphan*/ ) ; 

int vgic_v4_flush_hwstate(struct kvm_vcpu *vcpu)
{
	int irq = vcpu->arch.vgic_cpu.vgic_v3.its_vpe.irq;
	int err;

	if (!vgic_supports_direct_msis(vcpu->kvm))
		return 0;

	/*
	 * Before making the VPE resident, make sure the redistributor
	 * corresponding to our current CPU expects us here. See the
	 * doc in drivers/irqchip/irq-gic-v4.c to understand how this
	 * turns into a VMOVP command at the ITS level.
	 */
	err = irq_set_affinity(irq, cpumask_of(smp_processor_id()));
	if (err)
		return err;

	err = its_schedule_vpe(&vcpu->arch.vgic_cpu.vgic_v3.its_vpe, true);
	if (err)
		return err;

	/*
	 * Now that the VPE is resident, let's get rid of a potential
	 * doorbell interrupt that would still be pending.
	 */
	err = irq_set_irqchip_state(irq, IRQCHIP_STATE_PENDING, false);

	return err;
}