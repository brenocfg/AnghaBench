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
struct snd_es1688 {scalar_t__ hardware; scalar_t__ irq; scalar_t__ dma8; int /*<<< orphan*/  res_port; } ;

/* Variables and functions */
 scalar_t__ ES1688_HW_UNDEF ; 
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1688_init (struct snd_es1688*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_es1688_free(struct snd_es1688 *chip)
{
	if (chip->hardware != ES1688_HW_UNDEF)
		snd_es1688_init(chip, 0);
	release_and_free_resource(chip->res_port);
	if (chip->irq >= 0)
		free_irq(chip->irq, (void *) chip);
	if (chip->dma8 >= 0) {
		disable_dma(chip->dma8);
		free_dma(chip->dma8);
	}
	return 0;
}