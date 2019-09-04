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
struct ni_private {int clock_and_fout; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_CONFIG_GET_CLOCK_SRC 131 
#define  INSN_CONFIG_SET_CLOCK_SRC 130 
 int /*<<< orphan*/  NISTC_CLK_FOUT_REG ; 
 int NISTC_CLK_FOUT_TIMEBASE_SEL ; 
#define  NI_FREQ_OUT_TIMEBASE_1_DIV_2_CLOCK_SRC 129 
#define  NI_FREQ_OUT_TIMEBASE_2_CLOCK_SRC 128 
 int TIMEBASE_1_NS ; 
 unsigned int TIMEBASE_2_NS ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_freq_out_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	struct ni_private *devpriv = dev->private;

	switch (data[0]) {
	case INSN_CONFIG_SET_CLOCK_SRC:
		switch (data[1]) {
		case NI_FREQ_OUT_TIMEBASE_1_DIV_2_CLOCK_SRC:
			devpriv->clock_and_fout &= ~NISTC_CLK_FOUT_TIMEBASE_SEL;
			break;
		case NI_FREQ_OUT_TIMEBASE_2_CLOCK_SRC:
			devpriv->clock_and_fout |= NISTC_CLK_FOUT_TIMEBASE_SEL;
			break;
		default:
			return -EINVAL;
		}
		ni_stc_writew(dev, devpriv->clock_and_fout, NISTC_CLK_FOUT_REG);
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		if (devpriv->clock_and_fout & NISTC_CLK_FOUT_TIMEBASE_SEL) {
			data[1] = NI_FREQ_OUT_TIMEBASE_2_CLOCK_SRC;
			data[2] = TIMEBASE_2_NS;
		} else {
			data[1] = NI_FREQ_OUT_TIMEBASE_1_DIV_2_CLOCK_SRC;
			data[2] = TIMEBASE_1_NS * 2;
		}
		break;
	default:
		return -EINVAL;
	}
	return insn->n;
}