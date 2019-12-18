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
struct vgic_irq {int group; int /*<<< orphan*/  mpidr; int /*<<< orphan*/  targets; int /*<<< orphan*/  refcount; struct kvm_vcpu* target_vcpu; int /*<<< orphan*/ * vcpu; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  ap_list; scalar_t__ intid; } ;
struct vgic_dist {int vgic_model; struct vgic_irq* spis; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {struct vgic_dist vgic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  KVM_DEV_TYPE_ARM_VGIC_V2 129 
#define  KVM_DEV_TYPE_ARM_VGIC_V3 128 
 scalar_t__ VGIC_NR_PRIVATE_IRQS ; 
 struct vgic_irq* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vgic_irq*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct kvm_vcpu* kvm_get_vcpu (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_vgic_dist_init(struct kvm *kvm, unsigned int nr_spis)
{
	struct vgic_dist *dist = &kvm->arch.vgic;
	struct kvm_vcpu *vcpu0 = kvm_get_vcpu(kvm, 0);
	int i;

	dist->spis = kcalloc(nr_spis, sizeof(struct vgic_irq), GFP_KERNEL);
	if (!dist->spis)
		return  -ENOMEM;

	/*
	 * In the following code we do not take the irq struct lock since
	 * no other action on irq structs can happen while the VGIC is
	 * not initialized yet:
	 * If someone wants to inject an interrupt or does a MMIO access, we
	 * require prior initialization in case of a virtual GICv3 or trigger
	 * initialization when using a virtual GICv2.
	 */
	for (i = 0; i < nr_spis; i++) {
		struct vgic_irq *irq = &dist->spis[i];

		irq->intid = i + VGIC_NR_PRIVATE_IRQS;
		INIT_LIST_HEAD(&irq->ap_list);
		raw_spin_lock_init(&irq->irq_lock);
		irq->vcpu = NULL;
		irq->target_vcpu = vcpu0;
		kref_init(&irq->refcount);
		switch (dist->vgic_model) {
		case KVM_DEV_TYPE_ARM_VGIC_V2:
			irq->targets = 0;
			irq->group = 0;
			break;
		case KVM_DEV_TYPE_ARM_VGIC_V3:
			irq->mpidr = 0;
			irq->group = 1;
			break;
		default:
			kfree(dist->spis);
			return -EINVAL;
		}
	}
	return 0;
}