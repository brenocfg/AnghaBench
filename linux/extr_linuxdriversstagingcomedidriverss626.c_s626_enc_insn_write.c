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
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_preload (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  s626_pulse_index (struct comedi_device*,unsigned int) ; 
 int /*<<< orphan*/  s626_set_load_trig (struct comedi_device*,unsigned int,int) ; 

__attribute__((used)) static int s626_enc_insn_write(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);

	/* Set the preload register */
	s626_preload(dev, chan, data[0]);

	/*
	 * Software index pulse forces the preload register to load
	 * into the counter
	 */
	s626_set_load_trig(dev, chan, 0);
	s626_pulse_index(dev, chan);
	s626_set_load_trig(dev, chan, 2);

	return 1;
}