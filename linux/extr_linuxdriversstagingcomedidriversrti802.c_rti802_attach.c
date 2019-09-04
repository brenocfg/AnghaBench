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
struct rti802_private {int /*<<< orphan*/ ** range_type_list; int /*<<< orphan*/ * dac_coding; } ;
struct comedi_subdevice {int maxdata; int n_chan; int /*<<< orphan*/ ** range_table_list; int /*<<< orphan*/  insn_write; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  type; } ;
struct comedi_device {struct comedi_subdevice* subdevices; } ;
struct comedi_devconfig {scalar_t__* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 struct rti802_private* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int comedi_alloc_subdev_readback (struct comedi_subdevice*) ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_request_region (struct comedi_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  dac_2comp ; 
 int /*<<< orphan*/  dac_straight ; 
 int /*<<< orphan*/  range_bipolar10 ; 
 int /*<<< orphan*/  range_unipolar10 ; 
 int /*<<< orphan*/  rti802_ao_insn_write ; 

__attribute__((used)) static int rti802_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct rti802_private *devpriv;
	struct comedi_subdevice *s;
	int i;
	int ret;

	ret = comedi_request_region(dev, it->options[0], 0x04);
	if (ret)
		return ret;

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 1);
	if (ret)
		return ret;

	/* Analog Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->maxdata	= 0xfff;
	s->n_chan	= 8;
	s->insn_write	= rti802_ao_insn_write;

	ret = comedi_alloc_subdev_readback(s);
	if (ret)
		return ret;

	s->range_table_list = devpriv->range_type_list;
	for (i = 0; i < 8; i++) {
		devpriv->dac_coding[i] = (it->options[3 + 2 * i])
			? (dac_straight) : (dac_2comp);
		devpriv->range_type_list[i] = (it->options[2 + 2 * i])
			? &range_unipolar10 : &range_bipolar10;
	}

	return 0;
}