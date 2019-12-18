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
struct vgic_irq {int /*<<< orphan*/  host_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQCHIP_STATE_PENDING ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_irqchip_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void vgic_irq_set_phys_pending(struct vgic_irq *irq, bool pending)
{
	WARN_ON(irq_set_irqchip_state(irq->host_irq,
				      IRQCHIP_STATE_PENDING,
				      pending));
}