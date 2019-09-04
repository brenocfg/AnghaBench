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
struct pcl812_private {int ai_poll_ptr; struct comedi_isadma* dma; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_isadma_desc {int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  size; } ;
struct comedi_isadma {size_t cur_dma; struct comedi_isadma_desc* desc; } ;
struct comedi_device {struct pcl812_private* private; } ;

/* Variables and functions */
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcl812_ai_setup_dma (struct comedi_device*,struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  transfer_from_dma_buf (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void pcl812_handle_dma(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct pcl812_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	unsigned int nsamples;
	int bufptr;

	nsamples = comedi_bytes_to_samples(s, desc->size) -
		   devpriv->ai_poll_ptr;
	bufptr = devpriv->ai_poll_ptr;
	devpriv->ai_poll_ptr = 0;

	/* restart dma with the next buffer */
	dma->cur_dma = 1 - dma->cur_dma;
	pcl812_ai_setup_dma(dev, s, nsamples);

	transfer_from_dma_buf(dev, s, desc->virt_addr, bufptr, nsamples);
}