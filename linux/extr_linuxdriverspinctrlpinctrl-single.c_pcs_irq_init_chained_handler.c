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
struct pcs_soc_data {int irq; int /*<<< orphan*/  irq_status_mask; int /*<<< orphan*/  irq_enable_mask; } ;
struct TYPE_2__ {char const* name; int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_unmask; void* irq_mask; void* irq_ack; } ;
struct pcs_device {int size; int /*<<< orphan*/  domain; TYPE_1__ chip; int /*<<< orphan*/  irqs; struct pcs_soc_data socdata; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_NO_THREAD ; 
 int IRQF_SHARED ; 
 scalar_t__ PCS_QUIRK_HAS_SHARED_IRQ ; 
 int /*<<< orphan*/  irq_domain_add_simple (struct device_node*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pcs_soc_data*) ; 
 int /*<<< orphan*/  irq_set_chained_handler (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct pcs_soc_data*) ; 
 int /*<<< orphan*/  pcs_irq_chain_handler ; 
 int /*<<< orphan*/  pcs_irq_handler ; 
 void* pcs_irq_mask ; 
 int /*<<< orphan*/  pcs_irq_set_wake ; 
 int /*<<< orphan*/  pcs_irq_unmask ; 
 int /*<<< orphan*/  pcs_irqdomain_ops ; 
 int request_irq (int,int /*<<< orphan*/ ,int,char const*,struct pcs_soc_data*) ; 

__attribute__((used)) static int pcs_irq_init_chained_handler(struct pcs_device *pcs,
					struct device_node *np)
{
	struct pcs_soc_data *pcs_soc = &pcs->socdata;
	const char *name = "pinctrl";
	int num_irqs;

	if (!pcs_soc->irq_enable_mask ||
	    !pcs_soc->irq_status_mask) {
		pcs_soc->irq = -1;
		return -EINVAL;
	}

	INIT_LIST_HEAD(&pcs->irqs);
	pcs->chip.name = name;
	pcs->chip.irq_ack = pcs_irq_mask;
	pcs->chip.irq_mask = pcs_irq_mask;
	pcs->chip.irq_unmask = pcs_irq_unmask;
	pcs->chip.irq_set_wake = pcs_irq_set_wake;

	if (PCS_QUIRK_HAS_SHARED_IRQ) {
		int res;

		res = request_irq(pcs_soc->irq, pcs_irq_handler,
				  IRQF_SHARED | IRQF_NO_SUSPEND |
				  IRQF_NO_THREAD,
				  name, pcs_soc);
		if (res) {
			pcs_soc->irq = -1;
			return res;
		}
	} else {
		irq_set_chained_handler_and_data(pcs_soc->irq,
						 pcs_irq_chain_handler,
						 pcs_soc);
	}

	/*
	 * We can use the register offset as the hardirq
	 * number as irq_domain_add_simple maps them lazily.
	 * This way we can easily support more than one
	 * interrupt per function if needed.
	 */
	num_irqs = pcs->size;

	pcs->domain = irq_domain_add_simple(np, num_irqs, 0,
					    &pcs_irqdomain_ops,
					    pcs_soc);
	if (!pcs->domain) {
		irq_set_chained_handler(pcs_soc->irq, NULL);
		return -EINVAL;
	}

	return 0;
}