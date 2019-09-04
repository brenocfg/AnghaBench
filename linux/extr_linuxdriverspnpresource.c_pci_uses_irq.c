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
struct pnp_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int pci_uses_irq(struct pnp_dev *pnp, unsigned int irq)
{
#ifdef CONFIG_PCI
	struct pci_dev *pci = NULL;

	for_each_pci_dev(pci) {
		if (pci_dev_uses_irq(pnp, pci, irq)) {
			pci_dev_put(pci);
			return 1;
		}
	}
#endif
	return 0;
}