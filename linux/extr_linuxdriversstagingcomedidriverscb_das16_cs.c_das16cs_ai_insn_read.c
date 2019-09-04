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
struct das16cs_private {int misc1; int misc2; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct das16cs_private* private; } ;

/* Variables and functions */
 int AREF_DIFF ; 
 int CR_AREF (int /*<<< orphan*/ ) ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS16CS_AI_DATA_REG ; 
 scalar_t__ DAS16CS_AI_MUX_REG ; 
 int DAS16CS_AI_MUX_SINGLE_CHAN (int) ; 
 int DAS16CS_MISC1_AI_CONV_MASK ; 
 int DAS16CS_MISC1_INTE ; 
 int DAS16CS_MISC1_INT_SRC_MASK ; 
 scalar_t__ DAS16CS_MISC1_REG ; 
 int DAS16CS_MISC1_SEDIFF ; 
 int DAS16CS_MISC2_AI_GAIN_1 ; 
 int DAS16CS_MISC2_AI_GAIN_2 ; 
 int DAS16CS_MISC2_AI_GAIN_4 ; 
 int DAS16CS_MISC2_AI_GAIN_8 ; 
 int DAS16CS_MISC2_AI_GAIN_MASK ; 
 int DAS16CS_MISC2_BME ; 
 scalar_t__ DAS16CS_MISC2_REG ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das16cs_ai_eoc ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int das16cs_ai_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct das16cs_private *devpriv = dev->private;
	int chan = CR_CHAN(insn->chanspec);
	int range = CR_RANGE(insn->chanspec);
	int aref = CR_AREF(insn->chanspec);
	int ret;
	int i;

	outw(DAS16CS_AI_MUX_SINGLE_CHAN(chan),
	     dev->iobase + DAS16CS_AI_MUX_REG);

	/* disable interrupts, software convert */
	devpriv->misc1 &= ~(DAS16CS_MISC1_INTE | DAS16CS_MISC1_INT_SRC_MASK |
			      DAS16CS_MISC1_AI_CONV_MASK);
	if (aref == AREF_DIFF)
		devpriv->misc1 &= ~DAS16CS_MISC1_SEDIFF;
	else
		devpriv->misc1 |= DAS16CS_MISC1_SEDIFF;
	outw(devpriv->misc1, dev->iobase + DAS16CS_MISC1_REG);

	devpriv->misc2 &= ~(DAS16CS_MISC2_BME | DAS16CS_MISC2_AI_GAIN_MASK);
	switch (range) {
	case 0:
		devpriv->misc2 |= DAS16CS_MISC2_AI_GAIN_1;
		break;
	case 1:
		devpriv->misc2 |= DAS16CS_MISC2_AI_GAIN_2;
		break;
	case 2:
		devpriv->misc2 |= DAS16CS_MISC2_AI_GAIN_4;
		break;
	case 3:
		devpriv->misc2 |= DAS16CS_MISC2_AI_GAIN_8;
		break;
	}
	outw(devpriv->misc2, dev->iobase + DAS16CS_MISC2_REG);

	for (i = 0; i < insn->n; i++) {
		outw(0, dev->iobase + DAS16CS_AI_DATA_REG);

		ret = comedi_timeout(dev, s, insn, das16cs_ai_eoc, 0);
		if (ret)
			return ret;

		data[i] = inw(dev->iobase + DAS16CS_AI_DATA_REG);
	}

	return i;
}