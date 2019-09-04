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
struct comedi_subdevice {int io_bits; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned short PCI1723_DIO_CTRL_HDIO ; 
 unsigned short PCI1723_DIO_CTRL_LDIO ; 
 scalar_t__ PCI1723_DIO_CTRL_REG ; 
 int comedi_dio_insn_config (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

__attribute__((used)) static int pci1723_dio_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int mask = (chan < 8) ? 0x00ff : 0xff00;
	unsigned short mode = 0x0000;		/* assume output */
	int ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (ret)
		return ret;

	if (!(s->io_bits & 0x00ff))
		mode |= PCI1723_DIO_CTRL_LDIO;	/* low byte input */
	if (!(s->io_bits & 0xff00))
		mode |= PCI1723_DIO_CTRL_HDIO;	/* high byte input */
	outw(mode, dev->iobase + PCI1723_DIO_CTRL_REG);

	return insn->n;
}