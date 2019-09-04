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
struct pcl818_private {int ai_cmd_canceled; scalar_t__ ai_cmd_running; scalar_t__ usefifo; struct comedi_isadma* dma; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_isadma {int /*<<< orphan*/  chan; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct pcl818_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct TYPE_2__ {scalar_t__ scans_done; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCL818_CTRL_DISABLE_TRIG ; 
 scalar_t__ PCL818_CTRL_REG ; 
 scalar_t__ PCL818_FI_ENABLE ; 
 scalar_t__ PCL818_FI_FLUSH ; 
 scalar_t__ PCL818_FI_INTCLR ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_NONE ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_isadma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pcl818_ai_clear_eoc (struct comedi_device*) ; 

__attribute__((used)) static int pcl818_ai_cancel(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct pcl818_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_cmd *cmd = &s->async->cmd;

	if (!devpriv->ai_cmd_running)
		return 0;

	if (dma) {
		if (cmd->stop_src == TRIG_NONE ||
		    (cmd->stop_src == TRIG_COUNT &&
		     s->async->scans_done < cmd->stop_arg)) {
			if (!devpriv->ai_cmd_canceled) {
				/*
				 * Wait for running dma transfer to end,
				 * do cleanup in interrupt.
				 */
				devpriv->ai_cmd_canceled = 1;
				return 0;
			}
		}
		comedi_isadma_disable(dma->chan);
	}

	outb(PCL818_CTRL_DISABLE_TRIG, dev->iobase + PCL818_CTRL_REG);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, false);
	pcl818_ai_clear_eoc(dev);

	if (devpriv->usefifo) {	/*  FIFO shutdown */
		outb(0, dev->iobase + PCL818_FI_INTCLR);
		outb(0, dev->iobase + PCL818_FI_FLUSH);
		outb(0, dev->iobase + PCL818_FI_ENABLE);
	}
	devpriv->ai_cmd_running = 0;
	devpriv->ai_cmd_canceled = 0;

	return 0;
}