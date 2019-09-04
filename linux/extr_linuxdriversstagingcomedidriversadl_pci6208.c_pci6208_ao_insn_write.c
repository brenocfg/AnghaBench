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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI6208_AO_CONTROL (unsigned int) ; 
 int /*<<< orphan*/  comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci6208_ao_eoc ; 

__attribute__((used)) static int pci6208_ao_insn_write(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	int ret;
	int i;

	for (i = 0; i < insn->n; i++) {
		unsigned int val = data[i];

		/* D/A transfer rate is 2.2us */
		ret = comedi_timeout(dev, s, insn, pci6208_ao_eoc, 0);
		if (ret)
			return ret;

		/* the hardware expects two's complement values */
		outw(comedi_offset_munge(s, val),
		     dev->iobase + PCI6208_AO_CONTROL(chan));

		s->readback[chan] = val;
	}

	return insn->n;
}