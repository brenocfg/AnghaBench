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
struct pci_8255_boardinfo {int n_8255; int /*<<< orphan*/  dio_badr; scalar_t__ has_mite; int /*<<< orphan*/  name; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  mmio; struct comedi_subdevice* subdevices; int /*<<< orphan*/  iobase; int /*<<< orphan*/  board_name; struct pci_8255_boardinfo const* board_ptr; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (struct pci_8255_boardinfo*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int I8255_SIZE ; 
 int IORESOURCE_MEM ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_pci_enable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 struct pci_8255_boardinfo* pci_8255_boards ; 
 int pci_8255_mite_init (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int subdev_8255_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int) ; 
 int subdev_8255_mm_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pci_8255_auto_attach(struct comedi_device *dev,
				unsigned long context)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const struct pci_8255_boardinfo *board = NULL;
	struct comedi_subdevice *s;
	int ret;
	int i;

	if (context < ARRAY_SIZE(pci_8255_boards))
		board = &pci_8255_boards[context];
	if (!board)
		return -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	if (ret)
		return ret;

	if (board->has_mite) {
		ret = pci_8255_mite_init(pcidev);
		if (ret)
			return ret;
	}

	if ((pci_resource_flags(pcidev, board->dio_badr) & IORESOURCE_MEM)) {
		dev->mmio = pci_ioremap_bar(pcidev, board->dio_badr);
		if (!dev->mmio)
			return -ENOMEM;
	} else {
		dev->iobase = pci_resource_start(pcidev, board->dio_badr);
	}

	/*
	 * One, two, or four subdevices are setup by this driver depending
	 * on the number of channels provided by the board. Each subdevice
	 * has 24 channels supported by the 8255 module.
	 */
	ret = comedi_alloc_subdevices(dev, board->n_8255);
	if (ret)
		return ret;

	for (i = 0; i < board->n_8255; i++) {
		s = &dev->subdevices[i];
		if (dev->mmio)
			ret = subdev_8255_mm_init(dev, s, NULL, i * I8255_SIZE);
		else
			ret = subdev_8255_init(dev, s, NULL, i * I8255_SIZE);
		if (ret)
			return ret;
	}

	return 0;
}