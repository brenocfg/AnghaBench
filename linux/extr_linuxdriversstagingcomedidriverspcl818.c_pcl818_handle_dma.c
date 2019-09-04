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
struct pcl818_private {struct comedi_isadma* dma; } ;
struct comedi_subdevice {unsigned int maxdata; } ;
struct comedi_isadma_desc {unsigned short* virt_addr; int /*<<< orphan*/  size; } ;
struct comedi_isadma {size_t cur_dma; struct comedi_isadma_desc* desc; } ;
struct comedi_device {struct pcl818_private* private; } ;

/* Variables and functions */
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcl818_ai_setup_dma (struct comedi_device*,struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  pcl818_ai_write_sample (struct comedi_device*,struct comedi_subdevice*,unsigned int,unsigned int) ; 

__attribute__((used)) static void pcl818_handle_dma(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct pcl818_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	unsigned short *ptr = desc->virt_addr;
	unsigned int nsamples = comedi_bytes_to_samples(s, desc->size);
	unsigned int chan;
	unsigned int val;
	int i;

	/* restart dma with the next buffer */
	dma->cur_dma = 1 - dma->cur_dma;
	pcl818_ai_setup_dma(dev, s, nsamples);

	for (i = 0; i < nsamples; i++) {
		val = ptr[i];
		chan = val & 0xf;
		val = (val >> 4) & s->maxdata;
		if (!pcl818_ai_write_sample(dev, s, chan, val))
			break;
	}
}