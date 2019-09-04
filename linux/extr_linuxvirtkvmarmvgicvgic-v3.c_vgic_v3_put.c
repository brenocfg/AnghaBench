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
struct vgic_v3_cpu_if {int /*<<< orphan*/  vgic_vmcr; int /*<<< orphan*/  vgic_sre; } ;
struct TYPE_3__ {struct vgic_v3_cpu_if vgic_v3; } ;
struct TYPE_4__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vgic_v3_deactivate_traps (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  __vgic_v3_read_vmcr ; 
 int /*<<< orphan*/  __vgic_v3_save_aprs ; 
 scalar_t__ has_vhe () ; 
 int /*<<< orphan*/  kvm_call_hyp (int /*<<< orphan*/ ,...) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

void vgic_v3_put(struct kvm_vcpu *vcpu)
{
	struct vgic_v3_cpu_if *cpu_if = &vcpu->arch.vgic_cpu.vgic_v3;

	if (likely(cpu_if->vgic_sre))
		cpu_if->vgic_vmcr = kvm_call_hyp(__vgic_v3_read_vmcr);

	kvm_call_hyp(__vgic_v3_save_aprs, vcpu);

	if (has_vhe())
		__vgic_v3_deactivate_traps(vcpu);
}