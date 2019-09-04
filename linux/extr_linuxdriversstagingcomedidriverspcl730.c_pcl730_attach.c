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
struct pcl730_board {scalar_t__ n_ttl_chan; scalar_t__ has_ttl_io; scalar_t__ is_pcl725; scalar_t__ is_acl7225b; scalar_t__ is_ir104; scalar_t__ n_iso_in_chan; scalar_t__ has_readback; scalar_t__ n_iso_out_chan; int /*<<< orphan*/  n_subdevs; int /*<<< orphan*/  io_range; } ;
struct comedi_subdevice {int maxdata; void* private; void* insn_bits; int /*<<< orphan*/ * range_table; scalar_t__ n_chan; void* subdev_flags; void* type; int /*<<< orphan*/  state; } ;
struct comedi_device {struct comedi_subdevice* subdevices; struct pcl730_board* board_ptr; } ;
struct comedi_devconfig {int /*<<< orphan*/ * options; } ;

/* Variables and functions */
 void* COMEDI_SUBD_DI ; 
 void* COMEDI_SUBD_DO ; 
 void* SDF_READABLE ; 
 void* SDF_WRITABLE ; 
 int comedi_alloc_subdevices (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int comedi_request_region (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* pcl730_di_insn_bits ; 
 void* pcl730_do_insn_bits ; 
 int /*<<< orphan*/  pcl730_get_bits (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  range_digital ; 

__attribute__((used)) static int pcl730_attach(struct comedi_device *dev,
			 struct comedi_devconfig *it)
{
	const struct pcl730_board *board = dev->board_ptr;
	struct comedi_subdevice *s;
	int subdev;
	int ret;

	ret = comedi_request_region(dev, it->options[0], board->io_range);
	if (ret)
		return ret;

	ret = comedi_alloc_subdevices(dev, board->n_subdevs);
	if (ret)
		return ret;

	subdev = 0;

	if (board->n_iso_out_chan) {
		/* Isolated Digital Outputs */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= board->n_iso_out_chan;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl730_do_insn_bits;
		s->private	= (void *)0;

		/* get the initial state if supported */
		if (board->has_readback)
			s->state = pcl730_get_bits(dev, s);
	}

	if (board->n_iso_in_chan) {
		/* Isolated Digital Inputs */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= board->n_iso_in_chan;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl730_di_insn_bits;
		s->private	= board->is_ir104 ? (void *)4 :
				  board->is_acl7225b ? (void *)2 :
				  board->is_pcl725 ? (void *)1 : (void *)0;
	}

	if (board->has_ttl_io) {
		/* TTL Digital Outputs */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= board->n_ttl_chan;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl730_do_insn_bits;
		s->private	= (void *)2;

		/* TTL Digital Inputs */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= board->n_ttl_chan;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl730_di_insn_bits;
		s->private	= (void *)2;
	}

	return 0;
}