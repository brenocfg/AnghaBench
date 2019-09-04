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
struct comedi_subdevice {int n_chan; int maxdata; int state; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  type; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* subdevices; } ;
struct comedi_devconfig {int /*<<< orphan*/ * options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_DO ; 
 scalar_t__ PC263_DO_0_7_REG ; 
 scalar_t__ PC263_DO_8_15_REG ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_request_region (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  pc263_do_insn_bits ; 
 int /*<<< orphan*/  range_digital ; 

__attribute__((used)) static int pc263_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	int ret;

	ret = comedi_request_region(dev, it->options[0], 0x2);
	if (ret)
		return ret;

	ret = comedi_alloc_subdevices(dev, 1);
	if (ret)
		return ret;

	/* Digital Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pc263_do_insn_bits;

	/* read initial relay state */
	s->state = inb(dev->iobase + PC263_DO_0_7_REG) |
		   (inb(dev->iobase + PC263_DO_8_15_REG) << 8);

	return 0;
}