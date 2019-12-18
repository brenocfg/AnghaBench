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
struct snd_wss {scalar_t__ irq; int hwshare; scalar_t__ dma1; scalar_t__ dma2; scalar_t__ timer; int /*<<< orphan*/  card; int /*<<< orphan*/  res_cport; int /*<<< orphan*/  res_port; } ;

/* Variables and functions */
 int WSS_HWSHARE_DMA1 ; 
 int WSS_HWSHARE_DMA2 ; 
 int WSS_HWSHARE_IRQ ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  kfree (struct snd_wss*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_device_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_dma_disable (scalar_t__) ; 

__attribute__((used)) static int snd_wss_free(struct snd_wss *chip)
{
	release_and_free_resource(chip->res_port);
	release_and_free_resource(chip->res_cport);
	if (chip->irq >= 0) {
		disable_irq(chip->irq);
		if (!(chip->hwshare & WSS_HWSHARE_IRQ))
			free_irq(chip->irq, (void *) chip);
	}
	if (!(chip->hwshare & WSS_HWSHARE_DMA1) && chip->dma1 >= 0) {
		snd_dma_disable(chip->dma1);
		free_dma(chip->dma1);
	}
	if (!(chip->hwshare & WSS_HWSHARE_DMA2) &&
	    chip->dma2 >= 0 && chip->dma2 != chip->dma1) {
		snd_dma_disable(chip->dma2);
		free_dma(chip->dma2);
	}
	if (chip->timer)
		snd_device_free(chip->card, chip->timer);
	kfree(chip);
	return 0;
}