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
struct snd_gus_card {int dummy; } ;
struct snd_card {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (long*) ; 
 int EBUSY ; 
 scalar_t__ SNDRV_AUTO_DMA ; 
 scalar_t__ SNDRV_AUTO_IRQ ; 
 long SNDRV_AUTO_PORT ; 
 int /*<<< orphan*/ * channels ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__* dma1 ; 
 scalar_t__* dma2 ; 
 scalar_t__* irq ; 
 int /*<<< orphan*/ * pcm_channels ; 
 long* port ; 
 int snd_gus_create (struct snd_card*,long,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_gus_card**) ; 
 scalar_t__ snd_legacy_find_free_dma (int*) ; 
 scalar_t__ snd_legacy_find_free_irq (int*) ; 

__attribute__((used)) static int snd_gusclassic_create(struct snd_card *card,
				 struct device *dev, unsigned int n,
				 struct snd_gus_card **rgus)
{
	static long possible_ports[] = {0x220, 0x230, 0x240, 0x250, 0x260};
	static int possible_irqs[] = {5, 11, 12, 9, 7, 15, 3, 4, -1};
	static int possible_dmas[] = {5, 6, 7, 1, 3, -1};

	int i, error;

	if (irq[n] == SNDRV_AUTO_IRQ) {
		irq[n] = snd_legacy_find_free_irq(possible_irqs);
		if (irq[n] < 0) {
			dev_err(dev, "unable to find a free IRQ\n");
			return -EBUSY;
		}
	}
	if (dma1[n] == SNDRV_AUTO_DMA) {
		dma1[n] = snd_legacy_find_free_dma(possible_dmas);
		if (dma1[n] < 0) {
			dev_err(dev, "unable to find a free DMA1\n");
			return -EBUSY;
		}
	}
	if (dma2[n] == SNDRV_AUTO_DMA) {
		dma2[n] = snd_legacy_find_free_dma(possible_dmas);
		if (dma2[n] < 0) {
			dev_err(dev, "unable to find a free DMA2\n");
			return -EBUSY;
		}
	}

	if (port[n] != SNDRV_AUTO_PORT)
		return snd_gus_create(card, port[n], irq[n], dma1[n], dma2[n],
				0, channels[n], pcm_channels[n], 0, rgus);

	i = 0;
	do {
		port[n] = possible_ports[i];
		error = snd_gus_create(card, port[n], irq[n], dma1[n], dma2[n],
				0, channels[n], pcm_channels[n], 0, rgus);
	} while (error < 0 && ++i < ARRAY_SIZE(possible_ports));

	return error;
}