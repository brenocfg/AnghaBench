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
struct s526_private {int* gpct_config; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct s526_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_GPCT_PULSE_TRAIN_GENERATOR 130 
#define  INSN_CONFIG_GPCT_QUADRATURE_ENCODER 129 
#define  INSN_CONFIG_GPCT_SINGLE_PULSE_GENERATOR 128 
 scalar_t__ S526_GPCT_MODE_REG (unsigned int) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  s526_gpct_write (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int s526_gpct_winsn(struct comedi_device *dev,
			   struct comedi_subdevice *s,
			   struct comedi_insn *insn,
			   unsigned int *data)
{
	struct s526_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);

	inw(dev->iobase + S526_GPCT_MODE_REG(chan));	/* Is this required? */

	/*  Check what Application of Counter this channel is configured for */
	switch (devpriv->gpct_config[chan]) {
	case INSN_CONFIG_GPCT_PULSE_TRAIN_GENERATOR:
		/*
		 * data[0] contains the PULSE_WIDTH
		 * data[1] contains the PULSE_PERIOD
		 * @pre PULSE_PERIOD > PULSE_WIDTH > 0
		 * The above periods must be expressed as a multiple of the
		 * pulse frequency on the selected source
		 */
		if ((data[1] <= data[0]) || !data[0])
			return -EINVAL;
		/* to write the PULSE_WIDTH */
		/* fall through */
	case INSN_CONFIG_GPCT_QUADRATURE_ENCODER:
	case INSN_CONFIG_GPCT_SINGLE_PULSE_GENERATOR:
		s526_gpct_write(dev, chan, data[0]);
		break;

	default:
		return -EINVAL;
	}

	return insn->n;
}