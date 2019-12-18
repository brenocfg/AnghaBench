#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
typedef  int u32 ;
struct vgic_irq {unsigned int pending_latch; int /*<<< orphan*/  irq_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  pendbaser; } ;
struct TYPE_4__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_2__ arch; } ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 scalar_t__ GICR_PENDBASER_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int kvm_read_guest_lock (int /*<<< orphan*/ ,scalar_t__,unsigned int*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int vgic_copy_lpi_list (int /*<<< orphan*/ ,struct kvm_vcpu*,int**) ; 
 struct vgic_irq* vgic_get_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vgic_put_irq (int /*<<< orphan*/ ,struct vgic_irq*) ; 
 int /*<<< orphan*/  vgic_queue_irq_unlock (int /*<<< orphan*/ ,struct vgic_irq*,unsigned long) ; 

__attribute__((used)) static int its_sync_lpi_pending_table(struct kvm_vcpu *vcpu)
{
	gpa_t pendbase = GICR_PENDBASER_ADDRESS(vcpu->arch.vgic_cpu.pendbaser);
	struct vgic_irq *irq;
	int last_byte_offset = -1;
	int ret = 0;
	u32 *intids;
	int nr_irqs, i;
	unsigned long flags;
	u8 pendmask;

	nr_irqs = vgic_copy_lpi_list(vcpu->kvm, vcpu, &intids);
	if (nr_irqs < 0)
		return nr_irqs;

	for (i = 0; i < nr_irqs; i++) {
		int byte_offset, bit_nr;

		byte_offset = intids[i] / BITS_PER_BYTE;
		bit_nr = intids[i] % BITS_PER_BYTE;

		/*
		 * For contiguously allocated LPIs chances are we just read
		 * this very same byte in the last iteration. Reuse that.
		 */
		if (byte_offset != last_byte_offset) {
			ret = kvm_read_guest_lock(vcpu->kvm,
						  pendbase + byte_offset,
						  &pendmask, 1);
			if (ret) {
				kfree(intids);
				return ret;
			}
			last_byte_offset = byte_offset;
		}

		irq = vgic_get_irq(vcpu->kvm, NULL, intids[i]);
		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		irq->pending_latch = pendmask & (1U << bit_nr);
		vgic_queue_irq_unlock(vcpu->kvm, irq, flags);
		vgic_put_irq(vcpu->kvm, irq);
	}

	kfree(intids);

	return ret;
}