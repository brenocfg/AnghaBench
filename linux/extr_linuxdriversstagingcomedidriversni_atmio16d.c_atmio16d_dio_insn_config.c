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
struct comedi_device {scalar_t__ iobase; struct atmio16d_private* private; } ;
struct atmio16d_private {int com_reg_2_state; } ;

/* Variables and functions */
 int COMREG2_DOUTEN0 ; 
 int COMREG2_DOUTEN1 ; 
 scalar_t__ COM_REG_2 ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int comedi_dio_insn_config (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int atmio16d_dio_insn_config(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	struct atmio16d_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int mask;
	int ret;

	if (chan < 4)
		mask = 0x0f;
	else
		mask = 0xf0;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (ret)
		return ret;

	devpriv->com_reg_2_state &= ~(COMREG2_DOUTEN0 | COMREG2_DOUTEN1);
	if (s->io_bits & 0x0f)
		devpriv->com_reg_2_state |= COMREG2_DOUTEN0;
	if (s->io_bits & 0xf0)
		devpriv->com_reg_2_state |= COMREG2_DOUTEN1;
	outw(devpriv->com_reg_2_state, dev->iobase + COM_REG_2);

	return insn->n;
}