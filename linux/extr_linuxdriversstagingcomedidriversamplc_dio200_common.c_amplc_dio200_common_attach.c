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
struct dio200_board {int* sdtype; int /*<<< orphan*/ * sdinfo; int /*<<< orphan*/  n_subdevs; } ;
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; void* type; int /*<<< orphan*/  insn_config; int /*<<< orphan*/  insn_read; } ;
struct comedi_device {unsigned int n_subdevices; unsigned int irq; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  board_name; struct comedi_subdevice* read_subdev; struct comedi_subdevice* subdevices; struct dio200_board* board_ptr; } ;

/* Variables and functions */
 void* COMEDI_SUBD_TIMER ; 
 void* COMEDI_SUBD_UNUSED ; 
 int /*<<< orphan*/  DIO200_INT_SCE ; 
 int SDF_LSAMPL ; 
 int SDF_READABLE ; 
 int comedi_alloc_subdevices (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dio200_interrupt ; 
 int dio200_subdev_8254_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int dio200_subdev_8255_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int dio200_subdev_intr_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dio200_subdev_timer_config ; 
 int /*<<< orphan*/  dio200_subdev_timer_read ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct comedi_device*) ; 
#define  sd_8254 131 
#define  sd_8255 130 
#define  sd_intr 129 
#define  sd_timer 128 

int amplc_dio200_common_attach(struct comedi_device *dev, unsigned int irq,
			       unsigned long req_irq_flags)
{
	const struct dio200_board *board = dev->board_ptr;
	struct comedi_subdevice *s;
	unsigned int n;
	int ret;

	ret = comedi_alloc_subdevices(dev, board->n_subdevs);
	if (ret)
		return ret;

	for (n = 0; n < dev->n_subdevices; n++) {
		s = &dev->subdevices[n];
		switch (board->sdtype[n]) {
		case sd_8254:
			/* counter subdevice (8254) */
			ret = dio200_subdev_8254_init(dev, s,
						      board->sdinfo[n]);
			if (ret < 0)
				return ret;
			break;
		case sd_8255:
			/* digital i/o subdevice (8255) */
			ret = dio200_subdev_8255_init(dev, s,
						      board->sdinfo[n]);
			if (ret < 0)
				return ret;
			break;
		case sd_intr:
			/* 'INTERRUPT' subdevice */
			if (irq && !dev->read_subdev) {
				ret = dio200_subdev_intr_init(dev, s,
							      DIO200_INT_SCE,
							      board->sdinfo[n]);
				if (ret < 0)
					return ret;
				dev->read_subdev = s;
			} else {
				s->type = COMEDI_SUBD_UNUSED;
			}
			break;
		case sd_timer:
			s->type		= COMEDI_SUBD_TIMER;
			s->subdev_flags	= SDF_READABLE | SDF_LSAMPL;
			s->n_chan	= 1;
			s->maxdata	= 0xffffffff;
			s->insn_read	= dio200_subdev_timer_read;
			s->insn_config	= dio200_subdev_timer_config;
			break;
		default:
			s->type = COMEDI_SUBD_UNUSED;
			break;
		}
	}

	if (irq && dev->read_subdev) {
		if (request_irq(irq, dio200_interrupt, req_irq_flags,
				dev->board_name, dev) >= 0) {
			dev->irq = irq;
		} else {
			dev_warn(dev->class_dev,
				 "warning! irq %u unavailable!\n", irq);
		}
	}

	return 0;
}