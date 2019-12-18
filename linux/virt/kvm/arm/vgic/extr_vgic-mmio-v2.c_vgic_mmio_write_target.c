#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u8 ;
typedef  scalar_t__ u32 ;
struct vgic_irq {unsigned long targets; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  target_vcpu; } ;
struct kvm_vcpu {TYPE_1__* kvm; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_4__ {int /*<<< orphan*/  online_vcpus; } ;

/* Variables and functions */
 unsigned long GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ VGIC_ADDR_TO_INTID (int /*<<< orphan*/ ,int) ; 
 scalar_t__ VGIC_NR_PRIVATE_IRQS ; 
 int __ffs (long) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_get_vcpu (TYPE_1__*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vgic_irq* vgic_get_irq (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vgic_put_irq (TYPE_1__*,struct vgic_irq*) ; 

__attribute__((used)) static void vgic_mmio_write_target(struct kvm_vcpu *vcpu,
				   gpa_t addr, unsigned int len,
				   unsigned long val)
{
	u32 intid = VGIC_ADDR_TO_INTID(addr, 8);
	u8 cpu_mask = GENMASK(atomic_read(&vcpu->kvm->online_vcpus) - 1, 0);
	int i;
	unsigned long flags;

	/* GICD_ITARGETSR[0-7] are read-only */
	if (intid < VGIC_NR_PRIVATE_IRQS)
		return;

	for (i = 0; i < len; i++) {
		struct vgic_irq *irq = vgic_get_irq(vcpu->kvm, NULL, intid + i);
		int target;

		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		irq->targets = (val >> (i * 8)) & cpu_mask;
		target = irq->targets ? __ffs(irq->targets) : 0;
		irq->target_vcpu = kvm_get_vcpu(vcpu->kvm, target);

		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(vcpu->kvm, irq);
	}
}