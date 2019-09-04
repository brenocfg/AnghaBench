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
struct pcmda12_private {scalar_t__ simultaneous_xfer_mode; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  iobase; struct pcmda12_private* private; } ;

/* Variables and functions */
 int comedi_readback_insn_read (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcmda12_ao_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct pcmda12_private *devpriv = dev->private;

	/*
	 * Initiate simultaneaous xfer mode by reading one of the
	 * AO registers. All analog outputs will then be updated.
	 */
	if (devpriv->simultaneous_xfer_mode)
		inb(dev->iobase);

	return comedi_readback_insn_read(dev, s, insn, data);
}