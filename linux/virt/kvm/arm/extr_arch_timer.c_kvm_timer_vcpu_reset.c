#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timer_map {TYPE_5__* emul_ptimer; TYPE_4__* direct_ptimer; TYPE_2__* direct_vtimer; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct arch_timer_cpu {scalar_t__ enabled; } ;
struct TYPE_14__ {scalar_t__ cnt_ctl; } ;
struct TYPE_13__ {int /*<<< orphan*/  hrtimer; } ;
struct TYPE_11__ {int /*<<< orphan*/  irq; } ;
struct TYPE_12__ {TYPE_3__ irq; } ;
struct TYPE_9__ {int /*<<< orphan*/  irq; } ;
struct TYPE_10__ {TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_timer_map (struct kvm_vcpu*,struct timer_map*) ; 
 scalar_t__ irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_timer_update_irq (struct kvm_vcpu*,int,TYPE_6__*) ; 
 int /*<<< orphan*/  kvm_vgic_reset_mapped_irq (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_timer_cancel (int /*<<< orphan*/ *) ; 
 TYPE_6__* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_cpu* vcpu_timer (struct kvm_vcpu*) ; 
 TYPE_6__* vcpu_vtimer (struct kvm_vcpu*) ; 

int kvm_timer_vcpu_reset(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = vcpu_timer(vcpu);
	struct timer_map map;

	get_timer_map(vcpu, &map);

	/*
	 * The bits in CNTV_CTL are architecturally reset to UNKNOWN for ARMv8
	 * and to 0 for ARMv7.  We provide an implementation that always
	 * resets the timer to be disabled and unmasked and is compliant with
	 * the ARMv7 architecture.
	 */
	vcpu_vtimer(vcpu)->cnt_ctl = 0;
	vcpu_ptimer(vcpu)->cnt_ctl = 0;

	if (timer->enabled) {
		kvm_timer_update_irq(vcpu, false, vcpu_vtimer(vcpu));
		kvm_timer_update_irq(vcpu, false, vcpu_ptimer(vcpu));

		if (irqchip_in_kernel(vcpu->kvm)) {
			kvm_vgic_reset_mapped_irq(vcpu, map.direct_vtimer->irq.irq);
			if (map.direct_ptimer)
				kvm_vgic_reset_mapped_irq(vcpu, map.direct_ptimer->irq.irq);
		}
	}

	if (map.emul_ptimer)
		soft_timer_cancel(&map.emul_ptimer->hrtimer);

	return 0;
}