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
struct pcl812_private {int ai_dma; int ai_eos; unsigned int mode_reg_int; scalar_t__ ai_poll_ptr; struct comedi_isadma* dma; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_isadma {scalar_t__ cur_dma; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct pcl812_private* private; } ;
struct comedi_cmd {scalar_t__* chanlist; unsigned int chanlist_len; int flags; int convert_src; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CMDF_WAKE_EOS ; 
 unsigned int PCL812_CTRL_PACER_DMA_TRIG ; 
 unsigned int PCL812_CTRL_PACER_EOC_TRIG ; 
 scalar_t__ PCL812_CTRL_REG ; 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_8254_update_divisors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  pcl812_ai_set_chan_range (struct comedi_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  pcl812_ai_setup_dma (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcl812_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pcl812_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int ctrl = 0;
	unsigned int i;

	pcl812_ai_set_chan_range(dev, cmd->chanlist[0], 1);

	if (dma) {	/*  check if we can use DMA transfer */
		devpriv->ai_dma = 1;
		for (i = 1; i < cmd->chanlist_len; i++)
			if (cmd->chanlist[0] != cmd->chanlist[i]) {
				/*  we cann't use DMA :-( */
				devpriv->ai_dma = 0;
				break;
			}
	} else {
		devpriv->ai_dma = 0;
	}

	devpriv->ai_poll_ptr = 0;

	/*  don't we want wake up every scan? */
	if (cmd->flags & CMDF_WAKE_EOS) {
		devpriv->ai_eos = 1;

		/*  DMA is useless for this situation */
		if (cmd->chanlist_len == 1)
			devpriv->ai_dma = 0;
	}

	if (devpriv->ai_dma) {
		/* setup and enable dma for the first buffer */
		dma->cur_dma = 0;
		pcl812_ai_setup_dma(dev, s, 0);
	}

	switch (cmd->convert_src) {
	case TRIG_TIMER:
		comedi_8254_update_divisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
		break;
	}

	if (devpriv->ai_dma)
		ctrl |= PCL812_CTRL_PACER_DMA_TRIG;
	else
		ctrl |= PCL812_CTRL_PACER_EOC_TRIG;
	outb(devpriv->mode_reg_int | ctrl, dev->iobase + PCL812_CTRL_REG);

	return 0;
}