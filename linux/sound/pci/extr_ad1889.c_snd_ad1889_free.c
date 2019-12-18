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
struct snd_ad1889 {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  iobase; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int AD_CHAN_ADC ; 
 int AD_CHAN_WAV ; 
 int /*<<< orphan*/  AD_DMA_DISR ; 
 int AD_DMA_DISR_PMAI ; 
 int AD_DMA_DISR_PTAI ; 
 int /*<<< orphan*/  ad1889_channel_reset (struct snd_ad1889*,int) ; 
 int /*<<< orphan*/  ad1889_mute (struct snd_ad1889*) ; 
 int /*<<< orphan*/  ad1889_readl (struct snd_ad1889*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad1889_writel (struct snd_ad1889*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_ad1889*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_ad1889*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_ad1889_free(struct snd_ad1889 *chip)
{
	if (chip->irq < 0)
		goto skip_hw;

	spin_lock_irq(&chip->lock);

	ad1889_mute(chip);

	/* Turn off interrupt on count and zero DMA registers */
	ad1889_channel_reset(chip, AD_CHAN_WAV | AD_CHAN_ADC);

	/* clear DISR. If we don't, we'd better jump off the Eiffel Tower */
	ad1889_writel(chip, AD_DMA_DISR, AD_DMA_DISR_PTAI | AD_DMA_DISR_PMAI);
	ad1889_readl(chip, AD_DMA_DISR);	/* flush, dammit! */

	spin_unlock_irq(&chip->lock);

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);

skip_hw:
	iounmap(chip->iobase);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}