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
struct comedi_insn {int chanspec; int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int CR_ALT_SOURCE ; 
 unsigned int CR_CHAN (int) ; 
 int /*<<< orphan*/  NI67XX_AO_CAL_CHAN_SEL_REG ; 
 int cs5529_do_conversion (struct comedi_device*,unsigned short*) ; 
 int /*<<< orphan*/  ni_ao_win_outw (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs5529_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	int n, retval;
	unsigned short sample;
	unsigned int channel_select;
	const unsigned int INTERNAL_REF = 0x1000;

	/*
	 * Set calibration adc source.  Docs lie, reference select bits 8 to 11
	 * do nothing. bit 12 seems to chooses internal reference voltage, bit
	 * 13 causes the adc input to go overrange (maybe reads external
	 * reference?)
	 */
	if (insn->chanspec & CR_ALT_SOURCE)
		channel_select = INTERNAL_REF;
	else
		channel_select = CR_CHAN(insn->chanspec);
	ni_ao_win_outw(dev, channel_select, NI67XX_AO_CAL_CHAN_SEL_REG);

	for (n = 0; n < insn->n; n++) {
		retval = cs5529_do_conversion(dev, &sample);
		if (retval < 0)
			return retval;
		data[n] = sample;
	}
	return insn->n;
}