#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* chip; } ;
struct irq_desc {TYPE_2__ irq_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* irq_enable ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  irq_state_clr_disabled (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_state_clr_masked (struct irq_desc*) ; 
 int /*<<< orphan*/  irqd_irq_disabled (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  unmask_irq (struct irq_desc*) ; 

void irq_enable(struct irq_desc *desc)
{
	if (!irqd_irq_disabled(&desc->irq_data)) {
		unmask_irq(desc);
	} else {
		irq_state_clr_disabled(desc);
		if (desc->irq_data.chip->irq_enable) {
			desc->irq_data.chip->irq_enable(&desc->irq_data);
			irq_state_clr_masked(desc);
		} else {
			unmask_irq(desc);
		}
	}
}