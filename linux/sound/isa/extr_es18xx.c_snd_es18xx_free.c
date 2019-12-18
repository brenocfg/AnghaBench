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
struct snd_es18xx {scalar_t__ irq; scalar_t__ dma1; scalar_t__ dma2; int /*<<< orphan*/  res_mpu_port; int /*<<< orphan*/  res_ctrl_port; int /*<<< orphan*/  res_port; } ;
struct snd_card {struct snd_es18xx* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_es18xx_free(struct snd_card *card)
{
	struct snd_es18xx *chip = card->private_data;

	release_and_free_resource(chip->res_port);
	release_and_free_resource(chip->res_ctrl_port);
	release_and_free_resource(chip->res_mpu_port);
	if (chip->irq >= 0)
		free_irq(chip->irq, (void *) card);
	if (chip->dma1 >= 0) {
		disable_dma(chip->dma1);
		free_dma(chip->dma1);
	}
	if (chip->dma2 >= 0 && chip->dma1 != chip->dma2) {
		disable_dma(chip->dma2);
		free_dma(chip->dma2);
	}
	return 0;
}