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
struct vgic_irq {int hw; int /*<<< orphan*/ * get_input_level; scalar_t__ hwintid; } ;

/* Variables and functions */

__attribute__((used)) static inline void kvm_vgic_unmap_irq(struct vgic_irq *irq)
{
	irq->hw = false;
	irq->hwintid = 0;
	irq->get_input_level = NULL;
}