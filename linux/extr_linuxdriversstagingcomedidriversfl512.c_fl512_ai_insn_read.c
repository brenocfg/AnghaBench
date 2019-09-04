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
struct comedi_subdevice {unsigned int maxdata; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ FL512_AI_LSB_REG ; 
 scalar_t__ FL512_AI_MSB_REG ; 
 scalar_t__ FL512_AI_MUX_REG ; 
 scalar_t__ FL512_AI_START_CONV_REG ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int fl512_ai_insn_read(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val;
	int i;

	outb(chan, dev->iobase + FL512_AI_MUX_REG);

	for (i = 0; i < insn->n; i++) {
		outb(0, dev->iobase + FL512_AI_START_CONV_REG);

		/* XXX should test "done" flag instead of delay */
		usleep_range(30, 100);

		val = inb(dev->iobase + FL512_AI_LSB_REG);
		val |= (inb(dev->iobase + FL512_AI_MSB_REG) << 8);
		val &= s->maxdata;

		data[i] = val;
	}

	return insn->n;
}