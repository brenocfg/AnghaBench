#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct pc236_private {void* lcr_iobase; } ;
struct comedi_device {int /*<<< orphan*/  board_name; TYPE_1__* board_ptr; int /*<<< orphan*/  class_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int amplc_pc236_common_attach (struct comedi_device*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pc236_private* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int comedi_pci_enable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ pc236_pci_board ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static int pci236_auto_attach(struct comedi_device *dev,
			      unsigned long context_unused)
{
	struct pci_dev *pci_dev = comedi_to_pci_dev(dev);
	struct pc236_private *devpriv;
	unsigned long iobase;
	int ret;

	dev_info(dev->class_dev, "amplc_pci236: attach pci %s\n",
		 pci_name(pci_dev));

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	dev->board_ptr = &pc236_pci_board;
	dev->board_name = pc236_pci_board.name;
	ret = comedi_pci_enable(dev);
	if (ret)
		return ret;

	devpriv->lcr_iobase = pci_resource_start(pci_dev, 1);
	iobase = pci_resource_start(pci_dev, 2);
	return amplc_pc236_common_attach(dev, iobase, pci_dev->irq,
					 IRQF_SHARED);
}