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
struct comedi_device {int ioenabled; int /*<<< orphan*/  board_name; } ;

/* Variables and functions */
 int ENODEV ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 

int comedi_pci_enable(struct comedi_device *dev)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	int rc;

	if (!pcidev)
		return -ENODEV;

	rc = pci_enable_device(pcidev);
	if (rc < 0)
		return rc;

	rc = pci_request_regions(pcidev, dev->board_name);
	if (rc < 0)
		pci_disable_device(pcidev);
	else
		dev->ioenabled = true;

	return rc;
}