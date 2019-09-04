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
struct snd_ad1816a {scalar_t__ irq; scalar_t__ dma1; scalar_t__ dma2; int /*<<< orphan*/  res_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_disable (scalar_t__) ; 

__attribute__((used)) static int snd_ad1816a_free(struct snd_ad1816a *chip)
{
	release_and_free_resource(chip->res_port);
	if (chip->irq >= 0)
		free_irq(chip->irq, (void *) chip);
	if (chip->dma1 >= 0) {
		snd_dma_disable(chip->dma1);
		free_dma(chip->dma1);
	}
	if (chip->dma2 >= 0) {
		snd_dma_disable(chip->dma2);
		free_dma(chip->dma2);
	}
	return 0;
}