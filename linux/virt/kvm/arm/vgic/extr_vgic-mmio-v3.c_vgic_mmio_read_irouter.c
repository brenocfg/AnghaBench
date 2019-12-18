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
struct vgic_irq {int /*<<< orphan*/  mpidr; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int VGIC_ADDR_TO_INTID (int,int) ; 
 unsigned long extract_bytes (int /*<<< orphan*/ ,int,unsigned int) ; 
 struct vgic_irq* vgic_get_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vgic_put_irq (int /*<<< orphan*/ ,struct vgic_irq*) ; 

__attribute__((used)) static unsigned long vgic_mmio_read_irouter(struct kvm_vcpu *vcpu,
					    gpa_t addr, unsigned int len)
{
	int intid = VGIC_ADDR_TO_INTID(addr, 64);
	struct vgic_irq *irq = vgic_get_irq(vcpu->kvm, NULL, intid);
	unsigned long ret = 0;

	if (!irq)
		return 0;

	/* The upper word is RAZ for us. */
	if (!(addr & 4))
		ret = extract_bytes(READ_ONCE(irq->mpidr), addr & 7, len);

	vgic_put_irq(vcpu->kvm, irq);
	return ret;
}