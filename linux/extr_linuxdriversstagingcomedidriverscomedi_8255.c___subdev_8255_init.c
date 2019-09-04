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
struct subdev_8255_private {int (* io ) (struct comedi_device*,int,int,int,unsigned long) ;unsigned long regbase; } ;
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int /*<<< orphan*/  insn_config; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 int ENOMEM ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 struct subdev_8255_private* comedi_alloc_spriv (struct comedi_subdevice*,int) ; 
 int /*<<< orphan*/  range_digital ; 
 int /*<<< orphan*/  subdev_8255_do_config (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  subdev_8255_insn ; 
 int /*<<< orphan*/  subdev_8255_insn_config ; 
 int subdev_8255_io (struct comedi_device*,int,int,int,unsigned long) ; 
 int subdev_8255_mmio (struct comedi_device*,int,int,int,unsigned long) ; 

__attribute__((used)) static int __subdev_8255_init(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      int (*io)(struct comedi_device *dev,
					int dir, int port, int data,
					unsigned long regbase),
			      unsigned long regbase,
			      bool is_mmio)
{
	struct subdev_8255_private *spriv;

	spriv = comedi_alloc_spriv(s, sizeof(*spriv));
	if (!spriv)
		return -ENOMEM;

	if (io)
		spriv->io = io;
	else if (is_mmio)
		spriv->io = subdev_8255_mmio;
	else
		spriv->io = subdev_8255_io;
	spriv->regbase	= regbase;

	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 24;
	s->range_table	= &range_digital;
	s->maxdata	= 1;
	s->insn_bits	= subdev_8255_insn;
	s->insn_config	= subdev_8255_insn_config;

	subdev_8255_do_config(dev, s);

	return 0;
}