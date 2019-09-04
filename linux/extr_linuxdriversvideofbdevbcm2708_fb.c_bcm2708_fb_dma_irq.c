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
struct bcm2708_fb {int /*<<< orphan*/  dma_waitq; scalar_t__ dma_chan_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ BCM2708_DMA_CS ; 
 int /*<<< orphan*/  BCM2708_DMA_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t bcm2708_fb_dma_irq(int irq, void *cxt)
{
	struct bcm2708_fb *fb = cxt;

	/* FIXME: should read status register to check if this is
	 * actually interrupting us or not, in case this interrupt
	 * ever becomes shared amongst several DMA channels
	 *
	 * readl(dma_chan_base + BCM2708_DMA_CS) & BCM2708_DMA_IRQ;
	 */

	/* acknowledge the interrupt */
	writel(BCM2708_DMA_INT, fb->dma_chan_base + BCM2708_DMA_CS);

	wake_up(&fb->dma_waitq);
	return IRQ_HANDLED;
}