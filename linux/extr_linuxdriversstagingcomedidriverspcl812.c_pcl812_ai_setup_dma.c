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
struct pcl812_private {scalar_t__ ai_eos; struct comedi_isadma* dma; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_isadma_desc {unsigned int maxsize; int /*<<< orphan*/  size; } ;
struct comedi_isadma {size_t cur_dma; int /*<<< orphan*/  chan; struct comedi_isadma_desc* desc; } ;
struct comedi_device {struct pcl812_private* private; } ;

/* Variables and functions */
 unsigned int comedi_bytes_per_scan (struct comedi_subdevice*) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_isadma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_isadma_program (struct comedi_isadma_desc*) ; 
 unsigned int comedi_nsamples_left (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_samples_to_bytes (struct comedi_subdevice*,unsigned int) ; 

__attribute__((used)) static void pcl812_ai_setup_dma(struct comedi_device *dev,
				struct comedi_subdevice *s,
				unsigned int unread_samples)
{
	struct pcl812_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	unsigned int bytes;
	unsigned int max_samples;
	unsigned int nsamples;

	comedi_isadma_disable(dma->chan);

	/* if using EOS, adapt DMA buffer to one scan */
	bytes = devpriv->ai_eos ? comedi_bytes_per_scan(s) : desc->maxsize;
	max_samples = comedi_bytes_to_samples(s, bytes);

	/*
	 * Determine dma size based on the buffer size plus the number of
	 * unread samples and the number of samples remaining in the command.
	 */
	nsamples = comedi_nsamples_left(s, max_samples + unread_samples);
	if (nsamples > unread_samples) {
		nsamples -= unread_samples;
		desc->size = comedi_samples_to_bytes(s, nsamples);
		comedi_isadma_program(desc);
	}
}