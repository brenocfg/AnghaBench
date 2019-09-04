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
struct faraday_pci {int /*<<< orphan*/  irqdomain; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCI_NUM_INTX ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  faraday_pci_irq_handler ; 
 int /*<<< orphan*/  faraday_pci_irqdomain_ops ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct faraday_pci*) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct faraday_pci*) ; 
 struct device_node* of_get_next_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int of_irq_get (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int faraday_pci_setup_cascaded_irq(struct faraday_pci *p)
{
	struct device_node *intc = of_get_next_child(p->dev->of_node, NULL);
	int irq;
	int i;

	if (!intc) {
		dev_err(p->dev, "missing child interrupt-controller node\n");
		return -EINVAL;
	}

	/* All PCI IRQs cascade off this one */
	irq = of_irq_get(intc, 0);
	if (irq <= 0) {
		dev_err(p->dev, "failed to get parent IRQ\n");
		of_node_put(intc);
		return irq ?: -EINVAL;
	}

	p->irqdomain = irq_domain_add_linear(intc, PCI_NUM_INTX,
					     &faraday_pci_irqdomain_ops, p);
	of_node_put(intc);
	if (!p->irqdomain) {
		dev_err(p->dev, "failed to create Gemini PCI IRQ domain\n");
		return -EINVAL;
	}

	irq_set_chained_handler_and_data(irq, faraday_pci_irq_handler, p);

	for (i = 0; i < 4; i++)
		irq_create_mapping(p->irqdomain, i);

	return 0;
}