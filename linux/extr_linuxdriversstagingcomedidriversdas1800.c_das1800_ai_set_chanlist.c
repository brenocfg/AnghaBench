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
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 scalar_t__ DAS1800_QRAM ; 
 scalar_t__ DAS1800_QRAM_ADDRESS ; 
 scalar_t__ DAS1800_SELECT ; 
 unsigned int QRAM ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void das1800_ai_set_chanlist(struct comedi_device *dev,
				    unsigned int *chanlist, unsigned int len)
{
	unsigned long flags;
	unsigned int i;

	/* protects the indirect addressing selected by DAS1800_SELECT */
	spin_lock_irqsave(&dev->spinlock, flags);

	/* select QRAM register and set start address */
	outb(QRAM, dev->iobase + DAS1800_SELECT);
	outb(len - 1, dev->iobase + DAS1800_QRAM_ADDRESS);

	/* make channel / gain list */
	for (i = 0; i < len; i++) {
		unsigned int chan = CR_CHAN(chanlist[i]);
		unsigned int range = CR_RANGE(chanlist[i]);
		unsigned short val;

		val = chan | ((range & 0x3) << 8);
		outw(val, dev->iobase + DAS1800_QRAM);
	}

	/* finish write to QRAM */
	outb(len - 1, dev->iobase + DAS1800_QRAM_ADDRESS);

	spin_unlock_irqrestore(&dev->spinlock, flags);
}