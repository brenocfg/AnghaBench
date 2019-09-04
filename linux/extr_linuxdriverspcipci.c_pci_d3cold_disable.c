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
struct pci_dev {int no_d3cold; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_bridge_d3_update (struct pci_dev*) ; 

void pci_d3cold_disable(struct pci_dev *dev)
{
	if (!dev->no_d3cold) {
		dev->no_d3cold = true;
		pci_bridge_d3_update(dev);
	}
}