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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ PCIMDDA_DA_CHAN (unsigned int) ; 
 int comedi_readback_insn_read (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 

__attribute__((used)) static int cb_pcimdda_ao_insn_read(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);

	/* Initiate the simultaneous transfer */
	inw(dev->iobase + PCIMDDA_DA_CHAN(chan));

	return comedi_readback_insn_read(dev, s, insn, data);
}