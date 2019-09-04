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
struct keystone_pcie {int* legacy_host_irqs; int* msi_host_irqs; struct device_node* msi_intc_np; struct device_node* legacy_intc_np; TYPE_1__* pci; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_MSI_HOST_IRQS ; 
 int PCI_NUM_INTX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char*,int) ; 
 int irq_of_parse_and_map (struct device_node*,int) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int of_irq_count (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int ks_pcie_get_irq_controller_info(struct keystone_pcie *ks_pcie,
					   char *controller, int *num_irqs)
{
	int temp, max_host_irqs, legacy = 1, *host_irqs;
	struct device *dev = ks_pcie->pci->dev;
	struct device_node *np_pcie = dev->of_node, **np_temp;

	if (!strcmp(controller, "msi-interrupt-controller"))
		legacy = 0;

	if (legacy) {
		np_temp = &ks_pcie->legacy_intc_np;
		max_host_irqs = PCI_NUM_INTX;
		host_irqs = &ks_pcie->legacy_host_irqs[0];
	} else {
		np_temp = &ks_pcie->msi_intc_np;
		max_host_irqs = MAX_MSI_HOST_IRQS;
		host_irqs =  &ks_pcie->msi_host_irqs[0];
	}

	/* interrupt controller is in a child node */
	*np_temp = of_get_child_by_name(np_pcie, controller);
	if (!(*np_temp)) {
		dev_err(dev, "Node for %s is absent\n", controller);
		return -EINVAL;
	}

	temp = of_irq_count(*np_temp);
	if (!temp) {
		dev_err(dev, "No IRQ entries in %s\n", controller);
		of_node_put(*np_temp);
		return -EINVAL;
	}

	if (temp > max_host_irqs)
		dev_warn(dev, "Too many %s interrupts defined %u\n",
			(legacy ? "legacy" : "MSI"), temp);

	/*
	 * support upto max_host_irqs. In dt from index 0 to 3 (legacy) or 0 to
	 * 7 (MSI)
	 */
	for (temp = 0; temp < max_host_irqs; temp++) {
		host_irqs[temp] = irq_of_parse_and_map(*np_temp, temp);
		if (!host_irqs[temp])
			break;
	}

	of_node_put(*np_temp);

	if (temp) {
		*num_irqs = temp;
		return 0;
	}

	return -EINVAL;
}