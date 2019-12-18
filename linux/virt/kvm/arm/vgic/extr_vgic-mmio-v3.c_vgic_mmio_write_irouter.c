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
struct vgic_irq {unsigned long mpidr; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  target_vcpu; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
typedef  int gpa_t ;

/* Variables and functions */
 unsigned long GENMASK (int,int /*<<< orphan*/ ) ; 
 int VGIC_ADDR_TO_INTID (int,int) ; 
 int /*<<< orphan*/  kvm_mpidr_to_vcpu (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vgic_irq* vgic_get_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vgic_put_irq (int /*<<< orphan*/ ,struct vgic_irq*) ; 

__attribute__((used)) static void vgic_mmio_write_irouter(struct kvm_vcpu *vcpu,
				    gpa_t addr, unsigned int len,
				    unsigned long val)
{
	int intid = VGIC_ADDR_TO_INTID(addr, 64);
	struct vgic_irq *irq;
	unsigned long flags;

	/* The upper word is WI for us since we don't implement Aff3. */
	if (addr & 4)
		return;

	irq = vgic_get_irq(vcpu->kvm, NULL, intid);

	if (!irq)
		return;

	raw_spin_lock_irqsave(&irq->irq_lock, flags);

	/* We only care about and preserve Aff0, Aff1 and Aff2. */
	irq->mpidr = val & GENMASK(23, 0);
	irq->target_vcpu = kvm_mpidr_to_vcpu(vcpu->kvm, irq->mpidr);

	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
	vgic_put_irq(vcpu->kvm, irq);
}