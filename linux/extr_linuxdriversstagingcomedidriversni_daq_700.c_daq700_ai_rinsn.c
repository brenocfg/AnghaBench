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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ ADCLEAR_R ; 
 scalar_t__ ADFIFO_R ; 
 unsigned int AREF_DIFF ; 
 scalar_t__ CMD_R1 ; 
 scalar_t__ CMD_R2 ; 
 scalar_t__ CMD_R3 ; 
 unsigned int CMD_R3_DIFF ; 
 scalar_t__ CMO_R ; 
 unsigned int CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  daq700_ai_eoc ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int daq700_ai_rinsn(struct comedi_device *dev,
			   struct comedi_subdevice *s,
			   struct comedi_insn *insn, unsigned int *data)
{
	int n;
	int d;
	int ret;
	unsigned int chan	= CR_CHAN(insn->chanspec);
	unsigned int aref	= CR_AREF(insn->chanspec);
	unsigned int range	= CR_RANGE(insn->chanspec);
	unsigned int r3_bits	= 0;

	/* set channel input modes */
	if (aref == AREF_DIFF)
		r3_bits |= CMD_R3_DIFF;
	/* write channel mode/range */
	if (range >= 1)
		range++;        /* convert range to hardware value */
	outb(r3_bits | (range & 0x03), dev->iobase + CMD_R3);

	/* write channel to multiplexer */
	/* set mask scan bit high to disable scanning */
	outb(chan | 0x80, dev->iobase + CMD_R1);
	/* mux needs 2us to really settle [Fred Brooks]. */
	udelay(2);

	/* convert n samples */
	for (n = 0; n < insn->n; n++) {
		/* trigger conversion with out0 L to H */
		outb(0x00, dev->iobase + CMD_R2); /* enable ADC conversions */
		outb(0x30, dev->iobase + CMO_R); /* mode 0 out0 L, from H */
		outb(0x00, dev->iobase + ADCLEAR_R);	/* clear the ADC FIFO */
		/* read 16bit junk from FIFO to clear */
		inw(dev->iobase + ADFIFO_R);
		/* mode 1 out0 H, L to H, start conversion */
		outb(0x32, dev->iobase + CMO_R);

		/* wait for conversion to end */
		ret = comedi_timeout(dev, s, insn, daq700_ai_eoc, 0);
		if (ret)
			return ret;

		/* read data */
		d = inw(dev->iobase + ADFIFO_R);
		/* mangle the data as necessary */
		/* Bipolar Offset Binary: 0 to 4095 for -10 to +10 */
		d &= 0x0fff;
		d ^= 0x0800;
		data[n] = d;
	}
	return n;
}