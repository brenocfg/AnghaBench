#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct das6402_private {int /*<<< orphan*/  irq; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct das6402_private* private; } ;
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int DAS6402_AI_MUX_HI (unsigned int) ; 
 int DAS6402_AI_MUX_LO (unsigned int) ; 
 scalar_t__ DAS6402_AI_MUX_REG ; 
 int DAS6402_CTRL_INTE ; 
 int DAS6402_CTRL_IRQ (int /*<<< orphan*/ ) ; 
 int DAS6402_CTRL_PACER_TRIG ; 
 scalar_t__ DAS6402_CTRL_REG ; 
 int /*<<< orphan*/  DAS6402_MODE_FIFONEPTY ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_8254_update_divisors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das6402_ai_set_mode (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int das6402_ai_cmd(struct comedi_device *dev,
			  struct comedi_subdevice *s)
{
	struct das6402_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int chan_lo = CR_CHAN(cmd->chanlist[0]);
	unsigned int chan_hi = CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1]);

	das6402_ai_set_mode(dev, s, cmd->chanlist[0], DAS6402_MODE_FIFONEPTY);

	/* load the mux for chanlist conversion */
	outw(DAS6402_AI_MUX_HI(chan_hi) | DAS6402_AI_MUX_LO(chan_lo),
	     dev->iobase + DAS6402_AI_MUX_REG);

	comedi_8254_update_divisors(dev->pacer);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, true);

	/* enable interrupt and pacer trigger */
	outb(DAS6402_CTRL_INTE |
	     DAS6402_CTRL_IRQ(devpriv->irq) |
	     DAS6402_CTRL_PACER_TRIG, dev->iobase + DAS6402_CTRL_REG);

	return 0;
}