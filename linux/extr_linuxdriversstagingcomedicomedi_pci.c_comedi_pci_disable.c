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
struct comedi_device {int ioenabled; } ;

/* Variables and functions */
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

void comedi_pci_disable(struct comedi_device *dev)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);

	if (pcidev && dev->ioenabled) {
		pci_release_regions(pcidev);
		pci_disable_device(pcidev);
	}
	dev->ioenabled = false;
}