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
struct pcl818_private {int ai_cmd_running; scalar_t__ usefifo; scalar_t__ act_chanlist_pos; scalar_t__ ai_cmd_canceled; struct comedi_isadma* dma; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_isadma {scalar_t__ cur_dma; } ;
struct comedi_device {int /*<<< orphan*/  pacer; scalar_t__ iobase; int /*<<< orphan*/  irq; struct pcl818_private* private; } ;
struct comedi_cmd {scalar_t__ convert_src; int /*<<< orphan*/  chanlist; int /*<<< orphan*/  chanlist_len; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ PCL818_CNTENABLE_REG ; 
 unsigned int PCL818_CTRL_DMAE ; 
 unsigned int PCL818_CTRL_EXT_TRIG ; 
 unsigned int PCL818_CTRL_INTE ; 
 unsigned int PCL818_CTRL_IRQ (int /*<<< orphan*/ ) ; 
 unsigned int PCL818_CTRL_PACER_TRIG ; 
 scalar_t__ PCL818_CTRL_REG ; 
 scalar_t__ PCL818_FI_ENABLE ; 
 scalar_t__ TRIG_TIMER ; 
 unsigned int check_channel_list (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_8254_update_divisors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  pcl818_ai_setup_chanlist (struct comedi_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pcl818_ai_setup_dma (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcl818_ai_cmd(struct comedi_device *dev,
			 struct comedi_subdevice *s)
{
	struct pcl818_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int ctrl = 0;
	unsigned int seglen;

	if (devpriv->ai_cmd_running)
		return -EBUSY;

	seglen = check_channel_list(dev, s, cmd->chanlist, cmd->chanlist_len);
	if (seglen < 1)
		return -EINVAL;
	pcl818_ai_setup_chanlist(dev, cmd->chanlist, seglen);

	devpriv->ai_cmd_running = 1;
	devpriv->ai_cmd_canceled = 0;
	devpriv->act_chanlist_pos = 0;

	if (cmd->convert_src == TRIG_TIMER)
		ctrl |= PCL818_CTRL_PACER_TRIG;
	else
		ctrl |= PCL818_CTRL_EXT_TRIG;

	outb(0, dev->iobase + PCL818_CNTENABLE_REG);

	if (dma) {
		/* setup and enable dma for the first buffer */
		dma->cur_dma = 0;
		pcl818_ai_setup_dma(dev, s, 0);

		ctrl |= PCL818_CTRL_INTE | PCL818_CTRL_IRQ(dev->irq) |
			PCL818_CTRL_DMAE;
	} else if (devpriv->usefifo) {
		/* enable FIFO */
		outb(1, dev->iobase + PCL818_FI_ENABLE);
	} else {
		ctrl |= PCL818_CTRL_INTE | PCL818_CTRL_IRQ(dev->irq);
	}
	outb(ctrl, dev->iobase + PCL818_CTRL_REG);

	if (cmd->convert_src == TRIG_TIMER) {
		comedi_8254_update_divisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
	}

	return 0;
}