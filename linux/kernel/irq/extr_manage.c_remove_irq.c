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
struct irqaction {int /*<<< orphan*/  dev_id; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_irq (struct irq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_settings_is_per_cpu_devid (struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 

void remove_irq(unsigned int irq, struct irqaction *act)
{
	struct irq_desc *desc = irq_to_desc(irq);

	if (desc && !WARN_ON(irq_settings_is_per_cpu_devid(desc)))
		__free_irq(desc, act->dev_id);
}