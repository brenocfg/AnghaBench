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

/* Variables and functions */
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pcie_pme_can_wakeup(struct pci_dev *dev, void *ign)
{
	device_set_wakeup_capable(&dev->dev, true);
	return 0;
}