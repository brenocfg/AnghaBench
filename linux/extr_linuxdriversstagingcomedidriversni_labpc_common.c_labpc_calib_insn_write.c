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
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_caldac (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int labpc_calib_insn_write(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);

	/*
	 * Only write the last data value to the caldac. Preceding
	 * data would be overwritten anyway.
	 */
	if (insn->n > 0) {
		unsigned int val = data[insn->n - 1];

		if (s->readback[chan] != val) {
			write_caldac(dev, chan, val);
			s->readback[chan] = val;
		}
	}

	return insn->n;
}