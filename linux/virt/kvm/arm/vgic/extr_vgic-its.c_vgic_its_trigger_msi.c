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
typedef  int /*<<< orphan*/  u32 ;
struct vgic_its {int dummy; } ;
struct vgic_irq {int pending_latch; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  host_irq; scalar_t__ hw; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQCHIP_STATE_PENDING ; 
 int irq_set_irqchip_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int vgic_its_resolve_lpi (struct kvm*,struct vgic_its*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vgic_irq**) ; 
 int /*<<< orphan*/  vgic_queue_irq_unlock (struct kvm*,struct vgic_irq*,unsigned long) ; 

__attribute__((used)) static int vgic_its_trigger_msi(struct kvm *kvm, struct vgic_its *its,
				u32 devid, u32 eventid)
{
	struct vgic_irq *irq = NULL;
	unsigned long flags;
	int err;

	err = vgic_its_resolve_lpi(kvm, its, devid, eventid, &irq);
	if (err)
		return err;

	if (irq->hw)
		return irq_set_irqchip_state(irq->host_irq,
					     IRQCHIP_STATE_PENDING, true);

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	irq->pending_latch = true;
	vgic_queue_irq_unlock(kvm, irq, flags);

	return 0;
}