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
struct comedi_device {int dummy; } ;
struct comedi_devconfig {int* options; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  comedi_set_hw_dev (struct comedi_device*,int /*<<< orphan*/ *) ; 
 int pci9118_common_attach (struct comedi_device*,int,int) ; 
 struct pci_dev* pci9118_find_pci (struct comedi_device*,struct comedi_devconfig*) ; 

__attribute__((used)) static int pci9118_attach(struct comedi_device *dev,
			  struct comedi_devconfig *it)
{
	struct pci_dev *pcidev;
	int ext_mux, softsshdelay;

	ext_mux = it->options[2];
	softsshdelay = it->options[4];

	pcidev = pci9118_find_pci(dev, it);
	if (!pcidev)
		return -EIO;
	comedi_set_hw_dev(dev, &pcidev->dev);

	return pci9118_common_attach(dev, ext_mux, softsshdelay);
}