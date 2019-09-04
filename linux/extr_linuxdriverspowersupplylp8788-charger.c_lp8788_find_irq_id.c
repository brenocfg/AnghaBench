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
struct lp8788_charger {int num_irqs; TYPE_1__* irqs; } ;
struct TYPE_2__ {int virq; int which; } ;

/* Variables and functions */

__attribute__((used)) static bool lp8788_find_irq_id(struct lp8788_charger *pchg, int virq, int *id)
{
	bool found = false;
	int i;

	for (i = 0; i < pchg->num_irqs; i++) {
		if (pchg->irqs[i].virq == virq) {
			*id = pchg->irqs[i].which;
			found = true;
			break;
		}
	}

	return found;
}