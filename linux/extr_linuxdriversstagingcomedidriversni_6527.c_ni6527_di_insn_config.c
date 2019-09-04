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
struct ni6527_private {int filter_enable; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct ni6527_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_FILTER 128 
 int /*<<< orphan*/  ni6527_set_filter_enable (struct comedi_device*,int) ; 
 int /*<<< orphan*/  ni6527_set_filter_interval (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static int ni6527_di_insn_config(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	struct ni6527_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int interval;

	switch (data[0]) {
	case INSN_CONFIG_FILTER:
		/*
		 * The deglitch filter interval is specified in nanoseconds.
		 * The hardware supports intervals in 200ns increments. Round
		 * the user values up and return the actual interval.
		 */
		interval = (data[1] + 100) / 200;
		data[1] = interval * 200;

		if (interval) {
			ni6527_set_filter_interval(dev, interval);
			devpriv->filter_enable |= 1 << chan;
		} else {
			devpriv->filter_enable &= ~(1 << chan);
		}
		ni6527_set_filter_enable(dev, devpriv->filter_enable);
		break;
	default:
		return -EINVAL;
	}

	return insn->n;
}