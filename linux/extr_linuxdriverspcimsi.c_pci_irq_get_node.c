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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_first (struct cpumask const*) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int local_memory_node (int /*<<< orphan*/ ) ; 
 struct cpumask* pci_irq_get_affinity (struct pci_dev*,int) ; 

int pci_irq_get_node(struct pci_dev *pdev, int vec)
{
	const struct cpumask *mask;

	mask = pci_irq_get_affinity(pdev, vec);
	if (mask)
		return local_memory_node(cpu_to_node(cpumask_first(mask)));
	return dev_to_node(&pdev->dev);
}