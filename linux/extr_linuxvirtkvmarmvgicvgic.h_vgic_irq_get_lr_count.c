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
struct vgic_irq {int active; scalar_t__ source; int /*<<< orphan*/  intid; } ;

/* Variables and functions */
 int hweight8 (scalar_t__) ; 
 scalar_t__ irq_is_pending (struct vgic_irq*) ; 
 scalar_t__ vgic_irq_is_sgi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int vgic_irq_get_lr_count(struct vgic_irq *irq)
{
	/* Account for the active state as an interrupt */
	if (vgic_irq_is_sgi(irq->intid) && irq->source)
		return hweight8(irq->source) + irq->active;

	return irq_is_pending(irq) || irq->active;
}