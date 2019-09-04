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
struct comedi_device {unsigned long iobase; } ;

/* Variables and functions */
 unsigned int AREF_GROUND ; 
 unsigned int CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PCMMIO_AI_2ND_ADC_OFFSET ; 
 unsigned char PCMMIO_AI_CMD_CHAN_SEL (unsigned int) ; 
 unsigned char PCMMIO_AI_CMD_ODD_CHAN ; 
 unsigned char PCMMIO_AI_CMD_RANGE (unsigned int) ; 
 scalar_t__ PCMMIO_AI_CMD_REG ; 
 unsigned char PCMMIO_AI_CMD_SE ; 
 scalar_t__ PCMMIO_AI_LSB_REG ; 
 scalar_t__ PCMMIO_AI_MSB_REG ; 
 unsigned int comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  pcmmio_ai_eoc ; 

__attribute__((used)) static int pcmmio_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned long iobase = dev->iobase;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	unsigned int aref = CR_AREF(insn->chanspec);
	unsigned char cmd = 0;
	unsigned int val;
	int ret;
	int i;

	/*
	 * The PCM-MIO uses two Linear Tech LTC1859CG 8-channel A/D converters.
	 * The devices use a full duplex serial interface which transmits and
	 * receives data simultaneously. An 8-bit command is shifted into the
	 * ADC interface to configure it for the next conversion. At the same
	 * time, the data from the previous conversion is shifted out of the
	 * device. Consequently, the conversion result is delayed by one
	 * conversion from the command word.
	 *
	 * Setup the cmd for the conversions then do a dummy conversion to
	 * flush the junk data. Then do each conversion requested by the
	 * comedi_insn. Note that the last conversion will leave junk data
	 * in ADC which will get flushed on the next comedi_insn.
	 */

	if (chan > 7) {
		chan -= 8;
		iobase += PCMMIO_AI_2ND_ADC_OFFSET;
	}

	if (aref == AREF_GROUND)
		cmd |= PCMMIO_AI_CMD_SE;
	if (chan % 2)
		cmd |= PCMMIO_AI_CMD_ODD_CHAN;
	cmd |= PCMMIO_AI_CMD_CHAN_SEL(chan / 2);
	cmd |= PCMMIO_AI_CMD_RANGE(range);

	outb(cmd, iobase + PCMMIO_AI_CMD_REG);

	ret = comedi_timeout(dev, s, insn, pcmmio_ai_eoc, 0);
	if (ret)
		return ret;

	val = inb(iobase + PCMMIO_AI_LSB_REG);
	val |= inb(iobase + PCMMIO_AI_MSB_REG) << 8;

	for (i = 0; i < insn->n; i++) {
		outb(cmd, iobase + PCMMIO_AI_CMD_REG);

		ret = comedi_timeout(dev, s, insn, pcmmio_ai_eoc, 0);
		if (ret)
			return ret;

		val = inb(iobase + PCMMIO_AI_LSB_REG);
		val |= inb(iobase + PCMMIO_AI_MSB_REG) << 8;

		/* bipolar data is two's complement */
		if (comedi_range_is_bipolar(s, range))
			val = comedi_offset_munge(s, val);

		data[i] = val;
	}

	return insn->n;
}