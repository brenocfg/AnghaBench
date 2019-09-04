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
struct comedi_subdevice {int n_chan; int maxdata; int state; int /*<<< orphan*/  type; int /*<<< orphan*/  insn_config; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; } ;
struct comedi_device {struct comedi_subdevice* subdevices; int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_DI ; 
 int /*<<< orphan*/  COMEDI_SUBD_DO ; 
 int /*<<< orphan*/  COMEDI_SUBD_PWM ; 
 int /*<<< orphan*/  COMEDI_SUBD_UNUSED ; 
 int /*<<< orphan*/  PCI1760_CMD_GET_DO ; 
 int /*<<< orphan*/  SDF_PWM_COUNTER ; 
 int /*<<< orphan*/  SDF_READABLE ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_pci_enable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int pci1760_cmd (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci1760_di_insn_bits ; 
 int /*<<< orphan*/  pci1760_do_insn_bits ; 
 int /*<<< orphan*/  pci1760_pwm_insn_config ; 
 int /*<<< orphan*/  pci1760_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_digital ; 

__attribute__((used)) static int pci1760_auto_attach(struct comedi_device *dev,
			       unsigned long context)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	struct comedi_subdevice *s;
	int ret;

	ret = comedi_pci_enable(dev);
	if (ret)
		return ret;
	dev->iobase = pci_resource_start(pcidev, 0);

	pci1760_reset(dev);

	ret = comedi_alloc_subdevices(dev, 4);
	if (ret)
		return ret;

	/* Digital Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci1760_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci1760_do_insn_bits;

	/* get the current state of the outputs */
	ret = pci1760_cmd(dev, PCI1760_CMD_GET_DO, 0);
	if (ret < 0)
		return ret;
	s->state	= ret;

	/* PWM subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_PWM;
	s->subdev_flags	= SDF_PWM_COUNTER;
	s->n_chan	= 2;
	s->insn_config	= pci1760_pwm_insn_config;

	/* Counter subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_UNUSED;

	return 0;
}