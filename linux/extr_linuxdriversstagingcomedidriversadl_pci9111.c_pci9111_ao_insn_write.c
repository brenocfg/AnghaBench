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
 scalar_t__ PCI9111_AO_REG ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 

__attribute__((used)) static int pci9111_ao_insn_write(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val = s->readback[chan];
	int i;

	for (i = 0; i < insn->n; i++) {
		val = data[i];
		outw(val, dev->iobase + PCI9111_AO_REG);
	}
	s->readback[chan] = val;

	return insn->n;
}