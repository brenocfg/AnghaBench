#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct kvm_vcpu {TYPE_3__* kvm; } ;
struct TYPE_4__ {scalar_t__ vgic_model; } ;
struct TYPE_5__ {TYPE_1__ vgic; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 scalar_t__ KVM_DEV_TYPE_ARM_VGIC_V3 ; 
 scalar_t__ VGIC_NR_PRIVATE_IRQS ; 
 int /*<<< orphan*/  kvm_arm_halt_guest (TYPE_3__*) ; 

__attribute__((used)) static void vgic_change_active_prepare(struct kvm_vcpu *vcpu, u32 intid)
{
	if (vcpu->kvm->arch.vgic.vgic_model == KVM_DEV_TYPE_ARM_VGIC_V3 ||
	    intid > VGIC_NR_PRIVATE_IRQS)
		kvm_arm_halt_guest(vcpu->kvm);
}