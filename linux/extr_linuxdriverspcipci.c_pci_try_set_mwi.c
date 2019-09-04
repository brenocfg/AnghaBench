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
 int pci_set_mwi (struct pci_dev*) ; 

int pci_try_set_mwi(struct pci_dev *dev)
{
#ifdef PCI_DISABLE_MWI
	return 0;
#else
	return pci_set_mwi(dev);
#endif
}