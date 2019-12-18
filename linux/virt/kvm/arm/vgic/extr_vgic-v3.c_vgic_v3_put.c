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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vgic_v3_deactivate_traps (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  __vgic_v3_save_aprs ; 
 scalar_t__ has_vhe () ; 
 int /*<<< orphan*/  kvm_call_hyp (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_v3_vmcr_sync (struct kvm_vcpu*) ; 

void vgic_v3_put(struct kvm_vcpu *vcpu)
{
	vgic_v3_vmcr_sync(vcpu);

	kvm_call_hyp(__vgic_v3_save_aprs, vcpu);

	if (has_vhe())
		__vgic_v3_deactivate_traps(vcpu);
}