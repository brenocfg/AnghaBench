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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_isadma_desc {int size; int maxsize; int /*<<< orphan*/  chan; } ;
struct comedi_isadma {struct comedi_isadma_desc* desc; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  pacer; struct a2150_private* private; } ;
struct comedi_cmd {int flags; int chanlist_len; int scan_begin_arg; int stop_arg; scalar_t__ start_src; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {struct comedi_cmd cmd; } ;
struct a2150_private {unsigned int config_bits; int count; int irq_dma_bits; struct comedi_isadma* dma; } ;

/* Variables and functions */
 unsigned int AC0_BIT ; 
 unsigned int AC1_BIT ; 
 scalar_t__ AREF_OTHER ; 
 unsigned int CLOCK_MASK ; 
 int CMDF_PRIORITY ; 
 scalar_t__ CONFIG_REG ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int DELAY_TRIGGER_BITS ; 
 int DMA_EN_BIT ; 
 int DMA_INTR_EN_BIT ; 
 scalar_t__ DMA_TC_CLEAR_REG ; 
 scalar_t__ FIFO_RESET_REG ; 
 scalar_t__ FIFO_START_REG ; 
 unsigned int HW_TRIG_EN ; 
 int I8254_BINARY ; 
 int I8254_MODE0 ; 
 scalar_t__ IRQ_DMA_CNTRL_REG ; 
 unsigned int POST_TRIGGER_BITS ; 
 scalar_t__ TRIGGER_REG ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_NOW ; 
 scalar_t__ TRIG_OTHER ; 
 int /*<<< orphan*/  a2150_get_timing (struct comedi_device*,int*,int) ; 
 scalar_t__ a2150_set_chanlist (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  comedi_8254_load (int /*<<< orphan*/ ,int,int,int) ; 
 int comedi_bytes_per_sample (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  comedi_isadma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_isadma_program (struct comedi_isadma_desc*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 

__attribute__((used)) static int a2150_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct a2150_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc = &dma->desc[0];
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int old_config_bits = devpriv->config_bits;
	unsigned int trigger_bits;

	if (cmd->flags & CMDF_PRIORITY) {
		dev_err(dev->class_dev,
			"dma incompatible with hard real-time interrupt (CMDF_PRIORITY), aborting\n");
		return -1;
	}
	/* clear fifo and reset triggering circuitry */
	outw(0, dev->iobase + FIFO_RESET_REG);

	/* setup chanlist */
	if (a2150_set_chanlist(dev, CR_CHAN(cmd->chanlist[0]),
			       cmd->chanlist_len) < 0)
		return -1;

	/* setup ac/dc coupling */
	if (CR_AREF(cmd->chanlist[0]) == AREF_OTHER)
		devpriv->config_bits |= AC0_BIT;
	else
		devpriv->config_bits &= ~AC0_BIT;
	if (CR_AREF(cmd->chanlist[2]) == AREF_OTHER)
		devpriv->config_bits |= AC1_BIT;
	else
		devpriv->config_bits &= ~AC1_BIT;

	/* setup timing */
	a2150_get_timing(dev, &cmd->scan_begin_arg, cmd->flags);

	/* send timing, channel, config bits */
	outw(devpriv->config_bits, dev->iobase + CONFIG_REG);

	/* initialize number of samples remaining */
	devpriv->count = cmd->stop_arg * cmd->chanlist_len;

	comedi_isadma_disable(desc->chan);

	/* set size of transfer to fill in 1/3 second */
#define ONE_THIRD_SECOND 333333333
	desc->size = comedi_bytes_per_sample(s) * cmd->chanlist_len *
		    ONE_THIRD_SECOND / cmd->scan_begin_arg;
	if (desc->size > desc->maxsize)
		desc->size = desc->maxsize;
	if (desc->size < comedi_bytes_per_sample(s))
		desc->size = comedi_bytes_per_sample(s);
	desc->size -= desc->size % comedi_bytes_per_sample(s);

	comedi_isadma_program(desc);

	/*
	 * Clear dma interrupt before enabling it, to try and get rid of
	 * that one spurious interrupt that has been happening.
	 */
	outw(0x00, dev->iobase + DMA_TC_CLEAR_REG);

	/* enable dma on card */
	devpriv->irq_dma_bits |= DMA_INTR_EN_BIT | DMA_EN_BIT;
	outw(devpriv->irq_dma_bits, dev->iobase + IRQ_DMA_CNTRL_REG);

	/* may need to wait 72 sampling periods if timing was changed */
	comedi_8254_load(dev->pacer, 2, 72, I8254_MODE0 | I8254_BINARY);

	/* setup start triggering */
	trigger_bits = 0;
	/* decide if we need to wait 72 periods for valid data */
	if (cmd->start_src == TRIG_NOW &&
	    (old_config_bits & CLOCK_MASK) !=
	    (devpriv->config_bits & CLOCK_MASK)) {
		/* set trigger source to delay trigger */
		trigger_bits |= DELAY_TRIGGER_BITS;
	} else {
		/* otherwise no delay */
		trigger_bits |= POST_TRIGGER_BITS;
	}
	/* enable external hardware trigger */
	if (cmd->start_src == TRIG_EXT) {
		trigger_bits |= HW_TRIG_EN;
	} else if (cmd->start_src == TRIG_OTHER) {
		/*
		 * XXX add support for level/slope start trigger
		 * using TRIG_OTHER
		 */
		dev_err(dev->class_dev, "you shouldn't see this?\n");
	}
	/* send trigger config bits */
	outw(trigger_bits, dev->iobase + TRIGGER_REG);

	/* start acquisition for soft trigger */
	if (cmd->start_src == TRIG_NOW)
		outw(0, dev->iobase + FIFO_START_REG);

	return 0;
}