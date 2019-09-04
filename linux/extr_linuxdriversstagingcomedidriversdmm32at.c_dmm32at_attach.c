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
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int len_chanlist; int /*<<< orphan*/  insn_write; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; int /*<<< orphan*/  cancel; int /*<<< orphan*/  do_cmdtest; int /*<<< orphan*/  do_cmd; int /*<<< orphan*/  insn_read; } ;
struct comedi_device {struct comedi_subdevice* subdevices; struct comedi_subdevice* read_subdev; scalar_t__ irq; int /*<<< orphan*/  board_name; int /*<<< orphan*/  class_dev; } ;
struct comedi_devconfig {scalar_t__* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AI ; 
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int /*<<< orphan*/  DMM32AT_8255_IOBASE ; 
 int SDF_CMD_READ ; 
 int SDF_DIFF ; 
 int SDF_GROUND ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 int comedi_alloc_subdev_readback (struct comedi_subdevice*) ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_request_region (struct comedi_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmm32at_8255_io ; 
 int /*<<< orphan*/  dmm32at_ai_cancel ; 
 int /*<<< orphan*/  dmm32at_ai_cmd ; 
 int /*<<< orphan*/  dmm32at_ai_cmdtest ; 
 int /*<<< orphan*/  dmm32at_ai_insn_read ; 
 int /*<<< orphan*/  dmm32at_airanges ; 
 int /*<<< orphan*/  dmm32at_ao_insn_write ; 
 int /*<<< orphan*/  dmm32at_aoranges ; 
 int /*<<< orphan*/  dmm32at_isr ; 
 int dmm32at_reset (struct comedi_device*) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 
 int subdev_8255_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmm32at_attach(struct comedi_device *dev,
			  struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	int ret;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	if (ret)
		return ret;

	ret = dmm32at_reset(dev);
	if (ret) {
		dev_err(dev->class_dev, "board detection failed\n");
		return ret;
	}

	if (it->options[1]) {
		ret = request_irq(it->options[1], dmm32at_isr, 0,
				  dev->board_name, dev);
		if (ret == 0)
			dev->irq = it->options[1];
	}

	ret = comedi_alloc_subdevices(dev, 3);
	if (ret)
		return ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_DIFF;
	s->n_chan	= 32;
	s->maxdata	= 0xffff;
	s->range_table	= &dmm32at_airanges;
	s->insn_read	= dmm32at_ai_insn_read;
	if (dev->irq) {
		dev->read_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= s->n_chan;
		s->do_cmd	= dmm32at_ai_cmd;
		s->do_cmdtest	= dmm32at_ai_cmdtest;
		s->cancel	= dmm32at_ai_cancel;
	}

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 0x0fff;
	s->range_table	= &dmm32at_aoranges;
	s->insn_write	= dmm32at_ao_insn_write;

	ret = comedi_alloc_subdev_readback(s);
	if (ret)
		return ret;

	/* Digital I/O subdevice */
	s = &dev->subdevices[2];
	return subdev_8255_init(dev, s, dmm32at_8255_io, DMM32AT_8255_IOBASE);
}