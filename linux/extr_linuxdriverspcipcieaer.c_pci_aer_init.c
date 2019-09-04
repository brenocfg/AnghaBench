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
struct pci_dev {int /*<<< orphan*/  aer_stats; scalar_t__ aer_cap; } ;
struct aer_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cleanup_aer_error_status_regs (struct pci_dev*) ; 
 scalar_t__ pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 

void pci_aer_init(struct pci_dev *dev)
{
	dev->aer_cap = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR);

	if (dev->aer_cap)
		dev->aer_stats = kzalloc(sizeof(struct aer_stats), GFP_KERNEL);

	pci_cleanup_aer_error_status_regs(dev);
}