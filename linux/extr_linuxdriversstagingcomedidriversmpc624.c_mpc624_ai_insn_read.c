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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ MPC624_ADC ; 
 int MPC624_ADCS ; 
 int MPC624_ADSCK ; 
 scalar_t__ MPC624_GNMUXCH ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc624_ai_eoc ; 
 unsigned int mpc624_ai_get_sample (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mpc624_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	int ret;
	int i;

	/*
	 *  WARNING:
	 *  We always write 0 to GNSWA bit, so the channel range is +-/10.1Vdc
	 */
	outb(insn->chanspec, dev->iobase + MPC624_GNMUXCH);

	for (i = 0; i < insn->n; i++) {
		/*  Trigger the conversion */
		outb(MPC624_ADSCK, dev->iobase + MPC624_ADC);
		udelay(1);
		outb(MPC624_ADCS | MPC624_ADSCK, dev->iobase + MPC624_ADC);
		udelay(1);
		outb(0, dev->iobase + MPC624_ADC);
		udelay(1);

		/*  Wait for the conversion to end */
		ret = comedi_timeout(dev, s, insn, mpc624_ai_eoc, 0);
		if (ret)
			return ret;

		data[i] = mpc624_ai_get_sample(dev, s);
	}

	return insn->n;
}