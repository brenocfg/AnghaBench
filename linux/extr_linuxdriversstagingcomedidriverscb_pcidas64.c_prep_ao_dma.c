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
struct pcidas64_private {scalar_t__ main_iobase; int /*<<< orphan*/ * ao_bounce_buffer; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct comedi_subdevice* write_subdev; struct pcidas64_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct TYPE_2__ {scalar_t__ scans_done; } ;

/* Variables and functions */
 scalar_t__ ADC_QUEUE_CLEAR_REG ; 
 scalar_t__ DAC_BUFFER_CLEAR_REG ; 
 scalar_t__ DAC_FIFO_REG ; 
 int /*<<< orphan*/  DAC_FIFO_SIZE ; 
 scalar_t__ TRIG_COUNT ; 
 unsigned int cb_pcidas64_ao_fill_buffer (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_start_sync (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_ao_dma (struct comedi_device*,struct comedi_cmd const*) ; 
 unsigned int load_ao_dma_buffer (struct comedi_device*,struct comedi_cmd const*) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int prep_ao_dma(struct comedi_device *dev, const struct comedi_cmd *cmd)
{
	struct pcidas64_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->write_subdev;
	unsigned int nsamples;
	unsigned int nbytes;
	int i;

	/*
	 * clear queue pointer too, since external queue has
	 * weird interactions with ao fifo
	 */
	writew(0, devpriv->main_iobase + ADC_QUEUE_CLEAR_REG);
	writew(0, devpriv->main_iobase + DAC_BUFFER_CLEAR_REG);

	nsamples = cb_pcidas64_ao_fill_buffer(dev, s,
					      devpriv->ao_bounce_buffer,
					      DAC_FIFO_SIZE);
	if (nsamples == 0)
		return -1;

	for (i = 0; i < nsamples; i++) {
		writew(devpriv->ao_bounce_buffer[i],
		       devpriv->main_iobase + DAC_FIFO_REG);
	}

	if (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_done >= cmd->stop_arg)
		return 0;

	nbytes = load_ao_dma_buffer(dev, cmd);
	if (nbytes == 0)
		return -1;
	load_ao_dma(dev, cmd);

	dma_start_sync(dev, 0);

	return 0;
}