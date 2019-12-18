#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vgic_v3_cpu_if {struct kvm_vcpu* vgic_vmcr; int /*<<< orphan*/  vgic_sre; } ;
struct TYPE_3__ {struct vgic_v3_cpu_if vgic_v3; } ;
struct TYPE_4__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vgic_v3_activate_traps (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  __vgic_v3_restore_aprs ; 
 int /*<<< orphan*/  __vgic_v3_write_vmcr ; 
 scalar_t__ has_vhe () ; 
 int /*<<< orphan*/  kvm_call_hyp (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

void vgic_v3_load(struct kvm_vcpu *vcpu)
{
	struct vgic_v3_cpu_if *cpu_if = &vcpu->arch.vgic_cpu.vgic_v3;

	/*
	 * If dealing with a GICv2 emulation on GICv3, VMCR_EL2.VFIQen
	 * is dependent on ICC_SRE_EL1.SRE, and we have to perform the
	 * VMCR_EL2 save/restore in the world switch.
	 */
	if (likely(cpu_if->vgic_sre))
		kvm_call_hyp(__vgic_v3_write_vmcr, cpu_if->vgic_vmcr);

	kvm_call_hyp(__vgic_v3_restore_aprs, vcpu);

	if (has_vhe())
		__vgic_v3_activate_traps(vcpu);
}