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
struct intel_pinctrl {int ncommunities; struct intel_community* communities; } ;
struct intel_community {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  intel_gpio_community_irq_handler (struct intel_pinctrl*,struct intel_community const*) ; 

__attribute__((used)) static irqreturn_t intel_gpio_irq(int irq, void *data)
{
	const struct intel_community *community;
	struct intel_pinctrl *pctrl = data;
	irqreturn_t ret = IRQ_NONE;
	int i;

	/* Need to check all communities for pending interrupts */
	for (i = 0; i < pctrl->ncommunities; i++) {
		community = &pctrl->communities[i];
		ret |= intel_gpio_community_irq_handler(pctrl, community);
	}

	return ret;
}