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
 int __pci_enable_msi_range (struct pci_dev*,int,int,int /*<<< orphan*/ *) ; 

int pci_enable_msi(struct pci_dev *dev)
{
	int rc = __pci_enable_msi_range(dev, 1, 1, NULL);
	if (rc < 0)
		return rc;
	return 0;
}