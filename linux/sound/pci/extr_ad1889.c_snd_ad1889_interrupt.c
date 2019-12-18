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
struct snd_ad1889 {scalar_t__ csubs; scalar_t__ psubs; TYPE_1__* card; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_DMA_DISR ; 
 unsigned long AD_DMA_DISR_ADCI ; 
 unsigned long AD_DMA_DISR_PMAI ; 
 unsigned long AD_DMA_DISR_PTAI ; 
 unsigned long AD_DMA_DISR_WAVI ; 
 unsigned long AD_INTR_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long ad1889_readl (struct snd_ad1889*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad1889_writel (struct snd_ad1889*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t
snd_ad1889_interrupt(int irq, void *dev_id)
{
	unsigned long st;
	struct snd_ad1889 *chip = dev_id;

	st = ad1889_readl(chip, AD_DMA_DISR);

	/* clear ISR */
	ad1889_writel(chip, AD_DMA_DISR, st);

	st &= AD_INTR_MASK;

	if (unlikely(!st))
		return IRQ_NONE;

	if (st & (AD_DMA_DISR_PMAI|AD_DMA_DISR_PTAI))
		dev_dbg(chip->card->dev,
			"Unexpected master or target abort interrupt!\n");

	if ((st & AD_DMA_DISR_WAVI) && chip->psubs)
		snd_pcm_period_elapsed(chip->psubs);
	if ((st & AD_DMA_DISR_ADCI) && chip->csubs)
		snd_pcm_period_elapsed(chip->csubs);

	return IRQ_HANDLED;
}