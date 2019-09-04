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
struct das16_private_struct {int ctrl_reg; struct comedi_isadma* dma; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_isadma_desc {unsigned int size; int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  chan; } ;
struct comedi_isadma {size_t cur_dma; struct comedi_isadma_desc* desc; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  class_dev; struct comedi_subdevice* read_subdev; struct das16_private_struct* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct comedi_async {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int DAS16_CTRL_DMAE ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  comedi_bytes_per_sample (struct comedi_subdevice*) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int comedi_isadma_disable_on_sample (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das16_ai_setup_dma (struct comedi_device*,struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void das16_interrupt(struct comedi_device *dev)
{
	struct das16_private_struct *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	unsigned long spin_flags;
	unsigned int residue;
	unsigned int nbytes;
	unsigned int nsamples;

	spin_lock_irqsave(&dev->spinlock, spin_flags);
	if (!(devpriv->ctrl_reg & DAS16_CTRL_DMAE)) {
		spin_unlock_irqrestore(&dev->spinlock, spin_flags);
		return;
	}

	/*
	 * The pc104-das16jr (at least) has problems if the dma
	 * transfer is interrupted in the middle of transferring
	 * a 16 bit sample.
	 */
	residue = comedi_isadma_disable_on_sample(desc->chan,
						  comedi_bytes_per_sample(s));

	/* figure out how many samples to read */
	if (residue > desc->size) {
		dev_err(dev->class_dev, "residue > transfer size!\n");
		async->events |= COMEDI_CB_ERROR;
		nbytes = 0;
	} else {
		nbytes = desc->size - residue;
	}
	nsamples = comedi_bytes_to_samples(s, nbytes);

	/* restart DMA if more samples are needed */
	if (nsamples) {
		dma->cur_dma = 1 - dma->cur_dma;
		das16_ai_setup_dma(dev, s, nsamples);
	}

	spin_unlock_irqrestore(&dev->spinlock, spin_flags);

	comedi_buf_write_samples(s, desc->virt_addr, nsamples);

	if (cmd->stop_src == TRIG_COUNT && async->scans_done >= cmd->stop_arg)
		async->events |= COMEDI_CB_EOA;

	comedi_handle_events(dev, s);
}