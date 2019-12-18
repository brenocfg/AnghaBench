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
struct vgic_irq {int intid; int enabled; int /*<<< orphan*/  config; int /*<<< orphan*/  refcount; struct kvm_vcpu* target_vcpu; int /*<<< orphan*/ * vcpu; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  ap_list; } ;
struct vgic_dist {scalar_t__ vgic_model; } ;
struct TYPE_7__ {int /*<<< orphan*/  base_addr; } ;
struct vgic_cpu {struct vgic_irq* private_irqs; int /*<<< orphan*/  ap_list_lock; int /*<<< orphan*/  ap_list_head; TYPE_3__ rd_iodev; } ;
struct TYPE_5__ {struct vgic_cpu vgic_cpu; } ;
struct kvm_vcpu {TYPE_4__* kvm; TYPE_1__ arch; } ;
struct TYPE_6__ {struct vgic_dist vgic; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ KVM_DEV_TYPE_ARM_VGIC_V3 ; 
 int /*<<< orphan*/  VGIC_ADDR_UNDEF ; 
 int /*<<< orphan*/  VGIC_CONFIG_EDGE ; 
 int /*<<< orphan*/  VGIC_CONFIG_LEVEL ; 
 int VGIC_NR_PRIVATE_IRQS ; 
 int /*<<< orphan*/  irqchip_in_kernel (TYPE_4__*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ vgic_irq_is_sgi (int) ; 
 int vgic_register_redist_iodev (struct kvm_vcpu*) ; 

int kvm_vgic_vcpu_init(struct kvm_vcpu *vcpu)
{
	struct vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	struct vgic_dist *dist = &vcpu->kvm->arch.vgic;
	int ret = 0;
	int i;

	vgic_cpu->rd_iodev.base_addr = VGIC_ADDR_UNDEF;

	INIT_LIST_HEAD(&vgic_cpu->ap_list_head);
	raw_spin_lock_init(&vgic_cpu->ap_list_lock);

	/*
	 * Enable and configure all SGIs to be edge-triggered and
	 * configure all PPIs as level-triggered.
	 */
	for (i = 0; i < VGIC_NR_PRIVATE_IRQS; i++) {
		struct vgic_irq *irq = &vgic_cpu->private_irqs[i];

		INIT_LIST_HEAD(&irq->ap_list);
		raw_spin_lock_init(&irq->irq_lock);
		irq->intid = i;
		irq->vcpu = NULL;
		irq->target_vcpu = vcpu;
		kref_init(&irq->refcount);
		if (vgic_irq_is_sgi(i)) {
			/* SGIs */
			irq->enabled = 1;
			irq->config = VGIC_CONFIG_EDGE;
		} else {
			/* PPIs */
			irq->config = VGIC_CONFIG_LEVEL;
		}
	}

	if (!irqchip_in_kernel(vcpu->kvm))
		return 0;

	/*
	 * If we are creating a VCPU with a GICv3 we must also register the
	 * KVM io device for the redistributor that belongs to this VCPU.
	 */
	if (dist->vgic_model == KVM_DEV_TYPE_ARM_VGIC_V3) {
		mutex_lock(&vcpu->kvm->lock);
		ret = vgic_register_redist_iodev(vcpu);
		mutex_unlock(&vcpu->kvm->lock);
	}
	return ret;
}