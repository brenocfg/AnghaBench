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
struct vgic_irq {int (* get_input_level ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  host_irq; int /*<<< orphan*/  intid; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IRQCHIP_STATE_PENDING ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_get_irqchip_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

bool vgic_get_phys_line_level(struct vgic_irq *irq)
{
	bool line_level;

	BUG_ON(!irq->hw);

	if (irq->get_input_level)
		return irq->get_input_level(irq->intid);

	WARN_ON(irq_get_irqchip_state(irq->host_irq,
				      IRQCHIP_STATE_PENDING,
				      &line_level));
	return line_level;
}