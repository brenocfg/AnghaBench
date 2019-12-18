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
typedef  int /*<<< orphan*/  u32 ;
struct vgic_its {int /*<<< orphan*/  enabled; } ;
struct vgic_irq {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lpis_enabled; } ;
struct TYPE_5__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm {int dummy; } ;
struct its_ite {struct vgic_irq* irq; TYPE_3__* collection; } ;
struct TYPE_6__ {int /*<<< orphan*/  target_addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int E_ITS_INT_UNMAPPED_INTERRUPT ; 
 struct its_ite* find_ite (struct vgic_its*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_is_collection_mapped (TYPE_3__*) ; 
 struct kvm_vcpu* kvm_get_vcpu (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_its_cache_translation (struct kvm*,struct vgic_its*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vgic_irq*) ; 

int vgic_its_resolve_lpi(struct kvm *kvm, struct vgic_its *its,
			 u32 devid, u32 eventid, struct vgic_irq **irq)
{
	struct kvm_vcpu *vcpu;
	struct its_ite *ite;

	if (!its->enabled)
		return -EBUSY;

	ite = find_ite(its, devid, eventid);
	if (!ite || !its_is_collection_mapped(ite->collection))
		return E_ITS_INT_UNMAPPED_INTERRUPT;

	vcpu = kvm_get_vcpu(kvm, ite->collection->target_addr);
	if (!vcpu)
		return E_ITS_INT_UNMAPPED_INTERRUPT;

	if (!vcpu->arch.vgic_cpu.lpis_enabled)
		return -EBUSY;

	vgic_its_cache_translation(kvm, its, devid, eventid, ite->irq);

	*irq = ite->irq;
	return 0;
}