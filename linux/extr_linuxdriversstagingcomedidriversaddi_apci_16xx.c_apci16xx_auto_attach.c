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
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; scalar_t__ io_bits; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/  insn_config; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* subdevices; int /*<<< orphan*/  board_name; struct apci16xx_boardinfo const* board_ptr; } ;
struct apci16xx_boardinfo {int n_chan; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ APCI16XX_DIR_REG (int) ; 
 unsigned long ARRAY_SIZE (struct apci16xx_boardinfo*) ; 
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 int ENODEV ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 struct apci16xx_boardinfo* apci16xx_boardtypes ; 
 int /*<<< orphan*/  apci16xx_dio_insn_bits ; 
 int /*<<< orphan*/  apci16xx_insn_config ; 
 int comedi_alloc_subdevices (struct comedi_device*,unsigned int) ; 
 int comedi_pci_enable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  outl (scalar_t__,scalar_t__) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_digital ; 

__attribute__((used)) static int apci16xx_auto_attach(struct comedi_device *dev,
				unsigned long context)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const struct apci16xx_boardinfo *board = NULL;
	struct comedi_subdevice *s;
	unsigned int n_subdevs;
	unsigned int last;
	int i;
	int ret;

	if (context < ARRAY_SIZE(apci16xx_boardtypes))
		board = &apci16xx_boardtypes[context];
	if (!board)
		return -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	if (ret)
		return ret;

	dev->iobase = pci_resource_start(pcidev, 0);

	/*
	 * Work out the nubmer of subdevices needed to support all the
	 * digital i/o channels on the board. Each subdevice supports
	 * up to 32 channels.
	 */
	n_subdevs = board->n_chan / 32;
	if ((n_subdevs * 32) < board->n_chan) {
		last = board->n_chan - (n_subdevs * 32);
		n_subdevs++;
	} else {
		last = 0;
	}

	ret = comedi_alloc_subdevices(dev, n_subdevs);
	if (ret)
		return ret;

	/* Initialize the TTL digital i/o subdevices */
	for (i = 0; i < n_subdevs; i++) {
		s = &dev->subdevices[i];
		s->type		= COMEDI_SUBD_DIO;
		s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
		s->n_chan	= ((i * 32) < board->n_chan) ? 32 : last;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_config	= apci16xx_insn_config;
		s->insn_bits	= apci16xx_dio_insn_bits;

		/* Default all channels to inputs */
		s->io_bits	= 0;
		outl(s->io_bits, dev->iobase + APCI16XX_DIR_REG(i));
	}

	return 0;
}