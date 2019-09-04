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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vgic_its {int dummy; } ;
struct vgic_irq {int dummy; } ;
struct TYPE_8__ {scalar_t__ its_vm; } ;
struct TYPE_5__ {TYPE_4__ its_vpe; } ;
struct TYPE_6__ {TYPE_1__ vgic_v3; } ;
struct TYPE_7__ {TYPE_2__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct kvm {int dummy; } ;
struct its_collection {int /*<<< orphan*/  target_addr; } ;

/* Variables and functions */
 int E_ITS_INVALL_UNMAPPED_COLLECTION ; 
 struct its_collection* find_collection (struct vgic_its*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_cmd_get_collection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  its_invall_vpe (TYPE_4__*) ; 
 int /*<<< orphan*/  its_is_collection_mapped (struct its_collection*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct kvm_vcpu* kvm_get_vcpu (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_lpi_config (struct kvm*,struct vgic_irq*,struct kvm_vcpu*,int) ; 
 int vgic_copy_lpi_list (struct kvm*,struct kvm_vcpu*,int /*<<< orphan*/ **) ; 
 struct vgic_irq* vgic_get_irq (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_put_irq (struct kvm*,struct vgic_irq*) ; 

__attribute__((used)) static int vgic_its_cmd_handle_invall(struct kvm *kvm, struct vgic_its *its,
				      u64 *its_cmd)
{
	u32 coll_id = its_cmd_get_collection(its_cmd);
	struct its_collection *collection;
	struct kvm_vcpu *vcpu;
	struct vgic_irq *irq;
	u32 *intids;
	int irq_count, i;

	collection = find_collection(its, coll_id);
	if (!its_is_collection_mapped(collection))
		return E_ITS_INVALL_UNMAPPED_COLLECTION;

	vcpu = kvm_get_vcpu(kvm, collection->target_addr);

	irq_count = vgic_copy_lpi_list(kvm, vcpu, &intids);
	if (irq_count < 0)
		return irq_count;

	for (i = 0; i < irq_count; i++) {
		irq = vgic_get_irq(kvm, NULL, intids[i]);
		if (!irq)
			continue;
		update_lpi_config(kvm, irq, vcpu, false);
		vgic_put_irq(kvm, irq);
	}

	kfree(intids);

	if (vcpu->arch.vgic_cpu.vgic_v3.its_vpe.its_vm)
		its_invall_vpe(&vcpu->arch.vgic_cpu.vgic_v3.its_vpe);

	return 0;
}