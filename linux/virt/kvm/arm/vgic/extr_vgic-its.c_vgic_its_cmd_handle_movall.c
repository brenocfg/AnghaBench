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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct vgic_its {int dummy; } ;
struct vgic_irq {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm {int /*<<< orphan*/  online_vcpus; } ;

/* Variables and functions */
 int E_ITS_MOVALL_PROCNUM_OOR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ its_cmd_get_target_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ its_cmd_mask_field (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 struct kvm_vcpu* kvm_get_vcpu (struct kvm*,scalar_t__) ; 
 int /*<<< orphan*/  update_affinity (struct vgic_irq*,struct kvm_vcpu*) ; 
 int vgic_copy_lpi_list (struct kvm*,struct kvm_vcpu*,scalar_t__**) ; 
 struct vgic_irq* vgic_get_irq (struct kvm*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vgic_its_invalidate_cache (struct kvm*) ; 
 int /*<<< orphan*/  vgic_put_irq (struct kvm*,struct vgic_irq*) ; 

__attribute__((used)) static int vgic_its_cmd_handle_movall(struct kvm *kvm, struct vgic_its *its,
				      u64 *its_cmd)
{
	u32 target1_addr = its_cmd_get_target_addr(its_cmd);
	u32 target2_addr = its_cmd_mask_field(its_cmd, 3, 16, 32);
	struct kvm_vcpu *vcpu1, *vcpu2;
	struct vgic_irq *irq;
	u32 *intids;
	int irq_count, i;

	if (target1_addr >= atomic_read(&kvm->online_vcpus) ||
	    target2_addr >= atomic_read(&kvm->online_vcpus))
		return E_ITS_MOVALL_PROCNUM_OOR;

	if (target1_addr == target2_addr)
		return 0;

	vcpu1 = kvm_get_vcpu(kvm, target1_addr);
	vcpu2 = kvm_get_vcpu(kvm, target2_addr);

	irq_count = vgic_copy_lpi_list(kvm, vcpu1, &intids);
	if (irq_count < 0)
		return irq_count;

	for (i = 0; i < irq_count; i++) {
		irq = vgic_get_irq(kvm, NULL, intids[i]);

		update_affinity(irq, vcpu2);

		vgic_put_irq(kvm, irq);
	}

	vgic_its_invalidate_cache(kvm);

	kfree(intids);
	return 0;
}