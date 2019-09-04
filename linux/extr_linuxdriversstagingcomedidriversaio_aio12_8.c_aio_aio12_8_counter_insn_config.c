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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned int I8254_OSC_BASE_1MHZ ; 
#define  INSN_CONFIG_GET_CLOCK_SRC 128 

__attribute__((used)) static int aio_aio12_8_counter_insn_config(struct comedi_device *dev,
					   struct comedi_subdevice *s,
					   struct comedi_insn *insn,
					   unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);

	switch (data[0]) {
	case INSN_CONFIG_GET_CLOCK_SRC:
		/*
		 * Channels 0 and 2 have external clock sources.
		 * Channel 1 has a fixed 1 MHz clock source.
		 */
		data[0] = 0;
		data[1] = (chan == 1) ? I8254_OSC_BASE_1MHZ : 0;
		break;
	default:
		return -EINVAL;
	}

	return insn->n;
}