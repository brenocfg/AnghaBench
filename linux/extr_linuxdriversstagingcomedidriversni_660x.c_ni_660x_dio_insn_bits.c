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
struct comedi_subdevice {unsigned int state; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NI660X_DIO32_INPUT ; 
 int /*<<< orphan*/  NI660X_DIO32_OUTPUT ; 
 unsigned int ni_660x_read (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_660x_write (struct comedi_device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_660x_dio_insn_bits(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int shift = CR_CHAN(insn->chanspec);
	unsigned int mask = data[0] << shift;
	unsigned int bits = data[1] << shift;

	/*
	 * There are 40 channels in this subdevice but only 32 are usable
	 * as DIO. The shift adjusts the mask/bits to account for the base
	 * channel in insn->chanspec. The state update can then be handled
	 * normally for the 32 usable channels.
	 */
	if (mask) {
		s->state &= ~mask;
		s->state |= (bits & mask);
		ni_660x_write(dev, 0, s->state, NI660X_DIO32_OUTPUT);
	}

	/*
	 * Return the input channels, shifted back to account for the base
	 * channel.
	 */
	data[1] = ni_660x_read(dev, 0, NI660X_DIO32_INPUT) >> shift;

	return insn->n;
}