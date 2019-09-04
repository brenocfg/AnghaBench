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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pcie_flr (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_has_flr (struct pci_dev*) ; 

__attribute__((used)) static int delay_250ms_after_flr(struct pci_dev *dev, int probe)
{
	if (!pcie_has_flr(dev))
		return -ENOTTY;

	if (probe)
		return 0;

	pcie_flr(dev);

	msleep(250);

	return 0;
}