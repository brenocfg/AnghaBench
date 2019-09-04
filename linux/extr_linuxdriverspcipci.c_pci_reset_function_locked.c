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
struct pci_dev {int /*<<< orphan*/  reset_fn; } ;

/* Variables and functions */
 int ENOTTY ; 
 int __pci_reset_function_locked (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_restore (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_save_and_disable (struct pci_dev*) ; 

int pci_reset_function_locked(struct pci_dev *dev)
{
	int rc;

	if (!dev->reset_fn)
		return -ENOTTY;

	pci_dev_save_and_disable(dev);

	rc = __pci_reset_function_locked(dev);

	pci_dev_restore(dev);

	return rc;
}