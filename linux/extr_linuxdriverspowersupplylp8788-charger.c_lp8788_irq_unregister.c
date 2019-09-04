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
struct platform_device {int dummy; } ;
struct lp8788_charger {int num_irqs; TYPE_1__* irqs; } ;
struct TYPE_2__ {int virq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct lp8788_charger*) ; 

__attribute__((used)) static void lp8788_irq_unregister(struct platform_device *pdev,
				  struct lp8788_charger *pchg)
{
	int i;
	int irq;

	for (i = 0; i < pchg->num_irqs; i++) {
		irq = pchg->irqs[i].virq;
		if (!irq)
			continue;

		free_irq(irq, pchg);
	}
}