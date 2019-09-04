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
struct rti800_private {unsigned char muxgain_bits; scalar_t__ adc_2comp; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct rti800_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ RTI800_ADCHI ; 
 scalar_t__ RTI800_ADCLO ; 
 scalar_t__ RTI800_CLRFLAGS ; 
 scalar_t__ RTI800_CONVERT ; 
 scalar_t__ RTI800_MUXGAIN ; 
 unsigned int comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  rti800_ai_eoc ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rti800_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	struct rti800_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int gain = CR_RANGE(insn->chanspec);
	unsigned char muxgain_bits;
	int ret;
	int i;

	inb(dev->iobase + RTI800_ADCHI);
	outb(0, dev->iobase + RTI800_CLRFLAGS);

	muxgain_bits = chan | (gain << 5);
	if (muxgain_bits != devpriv->muxgain_bits) {
		devpriv->muxgain_bits = muxgain_bits;
		outb(devpriv->muxgain_bits, dev->iobase + RTI800_MUXGAIN);
		/*
		 * Without a delay here, the RTI_CSR_OVERRUN bit
		 * gets set, and you will have an error.
		 */
		if (insn->n > 0) {
			int delay = (gain == 0) ? 10 :
				    (gain == 1) ? 20 :
				    (gain == 2) ? 40 : 80;

			udelay(delay);
		}
	}

	for (i = 0; i < insn->n; i++) {
		unsigned int val;

		outb(0, dev->iobase + RTI800_CONVERT);

		ret = comedi_timeout(dev, s, insn, rti800_ai_eoc, 0);
		if (ret)
			return ret;

		val = inb(dev->iobase + RTI800_ADCLO);
		val |= (inb(dev->iobase + RTI800_ADCHI) & 0xf) << 8;

		if (devpriv->adc_2comp)
			val = comedi_offset_munge(s, val);

		data[i] = val;
	}

	return insn->n;
}