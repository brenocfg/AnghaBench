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
struct comedi_subdevice {int dummy; } ;
struct comedi_isadma_desc {int /*<<< orphan*/  chan; } ;
struct comedi_isadma {struct comedi_isadma_desc* desc; } ;
struct comedi_device {scalar_t__ iobase; struct a2150_private* private; } ;
struct a2150_private {int irq_dma_bits; struct comedi_isadma* dma; } ;

/* Variables and functions */
 int DMA_EN_BIT ; 
 int DMA_INTR_EN_BIT ; 
 scalar_t__ FIFO_RESET_REG ; 
 scalar_t__ IRQ_DMA_CNTRL_REG ; 
 int /*<<< orphan*/  comedi_isadma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int a2150_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct a2150_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc = &dma->desc[0];

	/* disable dma on card */
	devpriv->irq_dma_bits &= ~DMA_INTR_EN_BIT & ~DMA_EN_BIT;
	outw(devpriv->irq_dma_bits, dev->iobase + IRQ_DMA_CNTRL_REG);

	/* disable computer's dma */
	comedi_isadma_disable(desc->chan);

	/* clear fifo and reset triggering circuitry */
	outw(0, dev->iobase + FIFO_RESET_REG);

	return 0;
}