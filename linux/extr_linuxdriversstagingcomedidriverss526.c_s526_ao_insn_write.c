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
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int S526_AO_CTRL_CHAN (unsigned int) ; 
 scalar_t__ S526_AO_CTRL_REG ; 
 unsigned int S526_AO_CTRL_START ; 
 scalar_t__ S526_AO_REG ; 
 int /*<<< orphan*/  S526_INT_AO ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  s526_eoc ; 

__attribute__((used)) static int s526_ao_insn_write(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int ctrl = S526_AO_CTRL_CHAN(chan);
	unsigned int val = s->readback[chan];
	int ret;
	int i;

	outw(ctrl, dev->iobase + S526_AO_CTRL_REG);
	ctrl |= S526_AO_CTRL_START;

	for (i = 0; i < insn->n; i++) {
		val = data[i];
		outw(val, dev->iobase + S526_AO_REG);
		outw(ctrl, dev->iobase + S526_AO_CTRL_REG);

		/* wait for conversion to end */
		ret = comedi_timeout(dev, s, insn, s526_eoc, S526_INT_AO);
		if (ret)
			return ret;
	}
	s->readback[chan] = val;

	return insn->n;
}