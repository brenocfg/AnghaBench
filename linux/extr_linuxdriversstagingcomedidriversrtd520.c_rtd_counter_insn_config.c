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
struct rtd_private {unsigned int* timer_gate_src; unsigned int* timer_clk_src; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; struct rtd_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_GET_CLOCK_SRC 131 
#define  INSN_CONFIG_GET_GATE_SRC 130 
#define  INSN_CONFIG_SET_CLOCK_SRC 129 
#define  INSN_CONFIG_SET_GATE_SRC 128 
 scalar_t__ LAS0_8254_CLK_SEL (unsigned int) ; 
 scalar_t__ LAS0_8254_GATE_SEL (unsigned int) ; 
 unsigned int RTD_CLOCK_BASE ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int rtd_counter_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	struct rtd_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int max_src;
	unsigned int src;

	switch (data[0]) {
	case INSN_CONFIG_SET_GATE_SRC:
		/*
		 * 8254 Timer/Counter gate sources:
		 *
		 * 0 = Not gated, free running (reset state)
		 * 1 = Gated, off
		 * 2 = Ext. TC Gate 1
		 * 3 = Ext. TC Gate 2
		 * 4 = Previous TC out (chan 1 and 2 only)
		 */
		src = data[2];
		max_src = (chan == 0) ? 3 : 4;
		if (src > max_src)
			return -EINVAL;

		devpriv->timer_gate_src[chan] = src;
		writeb(src, dev->mmio + LAS0_8254_GATE_SEL(chan));
		break;
	case INSN_CONFIG_GET_GATE_SRC:
		data[2] = devpriv->timer_gate_src[chan];
		break;
	case INSN_CONFIG_SET_CLOCK_SRC:
		/*
		 * 8254 Timer/Counter clock sources:
		 *
		 * 0 = 8 MHz (reset state)
		 * 1 = Ext. TC Clock 1
		 * 2 = Ext. TX Clock 2
		 * 3 = Ext. Pacer Clock
		 * 4 = Previous TC out (chan 1 and 2 only)
		 * 5 = High-Speed Digital Input Sampling signal (chan 1 only)
		 */
		src = data[1];
		switch (chan) {
		case 0:
			max_src = 3;
			break;
		case 1:
			max_src = 5;
			break;
		case 2:
			max_src = 4;
			break;
		default:
			return -EINVAL;
		}
		if (src > max_src)
			return -EINVAL;

		devpriv->timer_clk_src[chan] = src;
		writeb(src, dev->mmio + LAS0_8254_CLK_SEL(chan));
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		src = devpriv->timer_clk_src[chan];
		data[1] = devpriv->timer_clk_src[chan];
		data[2] = (src == 0) ? RTD_CLOCK_BASE : 0;
		break;
	default:
		return -EINVAL;
	}

	return insn->n;
}