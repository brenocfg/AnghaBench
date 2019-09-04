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
struct pcl816_private {int dummy; } ;
struct pcl816_board {int ai_maxdata; int /*<<< orphan*/  ai_chanlist; } ;
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; int /*<<< orphan*/  cancel; int /*<<< orphan*/  poll; int /*<<< orphan*/  do_cmd; int /*<<< orphan*/  do_cmdtest; int /*<<< orphan*/  len_chanlist; int /*<<< orphan*/  insn_read; } ;
struct comedi_device {struct comedi_subdevice* subdevices; struct comedi_subdevice* read_subdev; scalar_t__ irq; int /*<<< orphan*/  pacer; scalar_t__ iobase; struct pcl816_board* board_ptr; } ;
struct comedi_devconfig {int /*<<< orphan*/ * options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AI ; 
 int /*<<< orphan*/  COMEDI_SUBD_DI ; 
 int /*<<< orphan*/  COMEDI_SUBD_DO ; 
 int /*<<< orphan*/  COMEDI_SUBD_UNUSED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I8254_IO8 ; 
 int /*<<< orphan*/  I8254_OSC_BASE_10MHZ ; 
 scalar_t__ PCL816_TIMER_BASE ; 
 int SDF_CMD_READ ; 
 int SDF_DIFF ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 int /*<<< orphan*/  comedi_8254_init (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcl816_private* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_request_region (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcl816_ai_cancel ; 
 int /*<<< orphan*/  pcl816_ai_cmd ; 
 int /*<<< orphan*/  pcl816_ai_cmdtest ; 
 int /*<<< orphan*/  pcl816_ai_insn_read ; 
 int /*<<< orphan*/  pcl816_ai_poll ; 
 int /*<<< orphan*/  pcl816_alloc_irq_and_dma (struct comedi_device*,struct comedi_devconfig*) ; 
 int /*<<< orphan*/  pcl816_di_insn_bits ; 
 int /*<<< orphan*/  pcl816_do_insn_bits ; 
 int /*<<< orphan*/  pcl816_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  range_digital ; 
 int /*<<< orphan*/  range_pcl816 ; 

__attribute__((used)) static int pcl816_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	const struct pcl816_board *board = dev->board_ptr;
	struct pcl816_private *devpriv;
	struct comedi_subdevice *s;
	int ret;

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	if (ret)
		return ret;

	/* an IRQ and DMA are required to support async commands */
	pcl816_alloc_irq_and_dma(dev, it);

	dev->pacer = comedi_8254_init(dev->iobase + PCL816_TIMER_BASE,
				      I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	if (!dev->pacer)
		return -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	if (ret)
		return ret;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_CMD_READ | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= board->ai_maxdata;
	s->range_table	= &range_pcl816;
	s->insn_read	= pcl816_ai_insn_read;
	if (dev->irq) {
		dev->read_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= board->ai_chanlist;
		s->do_cmdtest	= pcl816_ai_cmdtest;
		s->do_cmd	= pcl816_ai_cmd;
		s->poll		= pcl816_ai_poll;
		s->cancel	= pcl816_ai_cancel;
	}

	/* Piggyback Slot1 subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_UNUSED;

	/* Digital Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pcl816_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pcl816_do_insn_bits;

	pcl816_reset(dev);

	return 0;
}