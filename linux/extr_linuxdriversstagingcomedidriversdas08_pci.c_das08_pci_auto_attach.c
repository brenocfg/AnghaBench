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
struct das08_private_struct {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  iobase; int /*<<< orphan*/ * board_ptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct das08_private_struct* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int comedi_pci_enable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int das08_common_attach (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * das08_pci_boards ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static int das08_pci_auto_attach(struct comedi_device *dev,
				 unsigned long context_unused)
{
	struct pci_dev *pdev = comedi_to_pci_dev(dev);
	struct das08_private_struct *devpriv;
	int ret;

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	/* The das08 driver needs the board_ptr */
	dev->board_ptr = &das08_pci_boards[0];

	ret = comedi_pci_enable(dev);
	if (ret)
		return ret;
	dev->iobase = pci_resource_start(pdev, 2);

	return das08_common_attach(dev, dev->iobase);
}