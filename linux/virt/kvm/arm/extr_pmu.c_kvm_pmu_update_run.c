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
struct TYPE_7__ {scalar_t__ irq_level; } ;
struct TYPE_8__ {TYPE_3__ pmu; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_2__* run; } ;
struct kvm_sync_regs {int /*<<< orphan*/  device_irq_level; } ;
struct TYPE_5__ {struct kvm_sync_regs regs; } ;
struct TYPE_6__ {TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_ARM_DEV_PMU ; 

void kvm_pmu_update_run(struct kvm_vcpu *vcpu)
{
	struct kvm_sync_regs *regs = &vcpu->run->s.regs;

	/* Populate the timer bitmap for user space */
	regs->device_irq_level &= ~KVM_ARM_DEV_PMU;
	if (vcpu->arch.pmu.irq_level)
		regs->device_irq_level |= KVM_ARM_DEV_PMU;
}