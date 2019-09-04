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
struct comedi_device {int /*<<< orphan*/  spinlock; struct cb_pcidas_private* private; } ;
struct cb_pcidas_private {int ao_ctrl; scalar_t__ pcibar4; scalar_t__ pcibar1; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int PCIDAS_AO_DACEN ; 
 scalar_t__ PCIDAS_AO_DATA_REG (unsigned int) ; 
 int PCIDAS_AO_RANGE (unsigned int,unsigned int) ; 
 int PCIDAS_AO_RANGE_MASK (unsigned int) ; 
 scalar_t__ PCIDAS_AO_REG ; 
 int PCIDAS_AO_UPDATE_BOTH ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cb_pcidas_ao_nofifo_insn_write(struct comedi_device *dev,
					  struct comedi_subdevice *s,
					  struct comedi_insn *insn,
					  unsigned int *data)
{
	struct cb_pcidas_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	unsigned int val = s->readback[chan];
	unsigned long flags;
	int i;

	/* set channel and range */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->ao_ctrl &= ~(PCIDAS_AO_UPDATE_BOTH |
			      PCIDAS_AO_RANGE_MASK(chan));
	devpriv->ao_ctrl |= PCIDAS_AO_DACEN | PCIDAS_AO_RANGE(chan, range);
	outw(devpriv->ao_ctrl, devpriv->pcibar1 + PCIDAS_AO_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	for (i = 0; i < insn->n; i++) {
		val = data[i];
		outw(val, devpriv->pcibar4 + PCIDAS_AO_DATA_REG(chan));
	}

	s->readback[chan] = val;

	return insn->n;
}