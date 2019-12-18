#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct irq_chip* chip; } ;
struct irq_desc {TYPE_1__ irq_data; } ;
struct irq_chip {int flags; int /*<<< orphan*/  (* irq_eoi ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int IRQCHIP_EOI_THREADED ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  unmask_irq (struct irq_desc*) ; 

void unmask_threaded_irq(struct irq_desc *desc)
{
	struct irq_chip *chip = desc->irq_data.chip;

	if (chip->flags & IRQCHIP_EOI_THREADED)
		chip->irq_eoi(&desc->irq_data);

	unmask_irq(desc);
}