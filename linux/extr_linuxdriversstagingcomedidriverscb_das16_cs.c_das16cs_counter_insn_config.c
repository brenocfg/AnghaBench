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
struct das16cs_private {int misc2; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {scalar_t__ iobase; struct das16cs_private* private; } ;

/* Variables and functions */
 int DAS16CS_MISC2_CTR1 ; 
 scalar_t__ DAS16CS_MISC2_REG ; 
 int EINVAL ; 
 unsigned int I8254_OSC_BASE_100KHZ ; 
#define  INSN_CONFIG_GET_CLOCK_SRC 129 
#define  INSN_CONFIG_SET_CLOCK_SRC 128 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int das16cs_counter_insn_config(struct comedi_device *dev,
				       struct comedi_subdevice *s,
				       struct comedi_insn *insn,
				       unsigned int *data)
{
	struct das16cs_private *devpriv = dev->private;

	switch (data[0]) {
	case INSN_CONFIG_SET_CLOCK_SRC:
		switch (data[1]) {
		case 0:	/* internal 100 kHz */
			devpriv->misc2 |= DAS16CS_MISC2_CTR1;
			break;
		case 1:	/* external */
			devpriv->misc2 &= ~DAS16CS_MISC2_CTR1;
			break;
		default:
			return -EINVAL;
		}
		outw(devpriv->misc2, dev->iobase + DAS16CS_MISC2_REG);
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		if (devpriv->misc2 & DAS16CS_MISC2_CTR1) {
			data[1] = 0;
			data[2] = I8254_OSC_BASE_100KHZ;
		} else {
			data[1] = 1;
			data[2] = 0;	/* unknown */
		}
		break;
	default:
		return -EINVAL;
	}

	return insn->n;
}