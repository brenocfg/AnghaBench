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
struct comedi_subdevice {int subdev_flags; int maxdata; int /*<<< orphan*/  insn_config; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  n_chan; int /*<<< orphan*/  type; } ;
struct comedi_device {int /*<<< orphan*/  board_name; TYPE_1__* driver; int /*<<< orphan*/  class_dev; struct comedi_subdevice* subdevices; } ;
struct comedi_devconfig {int dummy; } ;
struct comedi_bond_private {int /*<<< orphan*/  ndevs; int /*<<< orphan*/  nchans; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 int ENOMEM ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 int /*<<< orphan*/  bonding_dio_insn_bits ; 
 int /*<<< orphan*/  bonding_dio_insn_config ; 
 struct comedi_bond_private* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_dev_config (struct comedi_device*,struct comedi_devconfig*) ; 
 int /*<<< orphan*/  range_digital ; 

__attribute__((used)) static int bonding_attach(struct comedi_device *dev,
			  struct comedi_devconfig *it)
{
	struct comedi_bond_private *devpriv;
	struct comedi_subdevice *s;
	int ret;

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	/*
	 * Setup our bonding from config params.. sets up our private struct..
	 */
	ret = do_dev_config(dev, it);
	if (ret)
		return ret;

	dev->board_name = devpriv->name;

	ret = comedi_alloc_subdevices(dev, 1);
	if (ret)
		return ret;

	s = &dev->subdevices[0];
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->n_chan = devpriv->nchans;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->insn_bits = bonding_dio_insn_bits;
	s->insn_config = bonding_dio_insn_config;

	dev_info(dev->class_dev,
		 "%s: %s attached, %u channels from %u devices\n",
		 dev->driver->driver_name, dev->board_name,
		 devpriv->nchans, devpriv->ndevs);

	return 0;
}