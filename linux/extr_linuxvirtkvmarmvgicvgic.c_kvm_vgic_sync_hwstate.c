#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vgic_cpu {scalar_t__ used_lrs; int /*<<< orphan*/  ap_list_head; } ;
struct TYPE_2__ {struct vgic_cpu vgic_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ can_access_vgic_from_kernel () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_fold_lr_state (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_prune_ap_list (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_save_state (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_v4_sync_hwstate (struct kvm_vcpu*) ; 

void kvm_vgic_sync_hwstate(struct kvm_vcpu *vcpu)
{
	struct vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;

	WARN_ON(vgic_v4_sync_hwstate(vcpu));

	/* An empty ap_list_head implies used_lrs == 0 */
	if (list_empty(&vcpu->arch.vgic_cpu.ap_list_head))
		return;

	if (can_access_vgic_from_kernel())
		vgic_save_state(vcpu);

	if (vgic_cpu->used_lrs)
		vgic_fold_lr_state(vcpu);
	vgic_prune_ap_list(vcpu);
}