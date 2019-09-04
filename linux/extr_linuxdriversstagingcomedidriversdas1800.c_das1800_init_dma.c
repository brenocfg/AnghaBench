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
struct das1800_private {scalar_t__ dma_bits; int /*<<< orphan*/  dma; } ;
struct comedi_device {struct das1800_private* private; } ;
struct comedi_devconfig {unsigned int* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_ISADMA_READ ; 
 int /*<<< orphan*/  DMA_BUF_SIZE ; 
 scalar_t__ DMA_CH5 ; 
 scalar_t__ DMA_CH5_CH6 ; 
 scalar_t__ DMA_CH6 ; 
 scalar_t__ DMA_CH6_CH7 ; 
 scalar_t__ DMA_CH7 ; 
 scalar_t__ DMA_CH7_CH5 ; 
 int /*<<< orphan*/  comedi_isadma_alloc (struct comedi_device*,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void das1800_init_dma(struct comedi_device *dev,
			     struct comedi_devconfig *it)
{
	struct das1800_private *devpriv = dev->private;
	unsigned int *dma_chan;

	/*
	 * it->options[2] is DMA channel 0
	 * it->options[3] is DMA channel 1
	 *
	 * Encode the DMA channels into 2 digit hexadecimal for switch.
	 */
	dma_chan = &it->options[2];

	switch ((dma_chan[0] & 0x7) | (dma_chan[1] << 4)) {
	case 0x5:	/*  dma0 == 5 */
		devpriv->dma_bits = DMA_CH5;
		break;
	case 0x6:	/*  dma0 == 6 */
		devpriv->dma_bits = DMA_CH6;
		break;
	case 0x7:	/*  dma0 == 7 */
		devpriv->dma_bits = DMA_CH7;
		break;
	case 0x65:	/*  dma0 == 5, dma1 == 6 */
		devpriv->dma_bits = DMA_CH5_CH6;
		break;
	case 0x76:	/*  dma0 == 6, dma1 == 7 */
		devpriv->dma_bits = DMA_CH6_CH7;
		break;
	case 0x57:	/*  dma0 == 7, dma1 == 5 */
		devpriv->dma_bits = DMA_CH7_CH5;
		break;
	default:
		return;
	}

	/* DMA can use 1 or 2 buffers, each with a separate channel */
	devpriv->dma = comedi_isadma_alloc(dev, dma_chan[1] ? 2 : 1,
					   dma_chan[0], dma_chan[1],
					   DMA_BUF_SIZE, COMEDI_ISADMA_READ);
	if (!devpriv->dma)
		devpriv->dma_bits = 0;
}