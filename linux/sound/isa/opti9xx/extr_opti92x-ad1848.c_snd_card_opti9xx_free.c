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
struct snd_opti9xx {scalar_t__ irq; int /*<<< orphan*/  res_mc_base; int /*<<< orphan*/  res_mc_indir; } ;
struct snd_card {struct snd_opti9xx* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_opti9xx*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_card_opti9xx_free(struct snd_card *card)
{
	struct snd_opti9xx *chip = card->private_data;

	if (chip) {
#ifdef OPTi93X
		if (chip->irq > 0) {
			disable_irq(chip->irq);
			free_irq(chip->irq, chip);
		}
		release_and_free_resource(chip->res_mc_indir);
#endif
		release_and_free_resource(chip->res_mc_base);
	}
}