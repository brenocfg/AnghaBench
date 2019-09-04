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
struct gb_gpio_controller {int line_max; int /*<<< orphan*/ * irqchip; scalar_t__ irqdomain; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (scalar_t__) ; 
 int /*<<< orphan*/  irq_find_mapping (scalar_t__,unsigned int) ; 

__attribute__((used)) static void gb_gpio_irqchip_remove(struct gb_gpio_controller *ggc)
{
	unsigned int offset;

	/* Remove all IRQ mappings and delete the domain */
	if (ggc->irqdomain) {
		for (offset = 0; offset < (ggc->line_max + 1); offset++)
			irq_dispose_mapping(irq_find_mapping(ggc->irqdomain,
							     offset));
		irq_domain_remove(ggc->irqdomain);
	}

	if (ggc->irqchip)
		ggc->irqchip = NULL;
}