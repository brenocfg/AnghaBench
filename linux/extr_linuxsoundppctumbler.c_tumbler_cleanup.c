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
struct snd_pmac {struct pmac_tumbler* mixer_data; } ;
struct pmac_tumbler {scalar_t__ headphone_irq; scalar_t__ lineout_irq; int /*<<< orphan*/  i2c; int /*<<< orphan*/  hp_detect; int /*<<< orphan*/  hp_mute; int /*<<< orphan*/  amp_mute; int /*<<< orphan*/  audio_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_pmac*) ; 
 int /*<<< orphan*/  kfree (struct pmac_tumbler*) ; 
 int /*<<< orphan*/  snd_pmac_keywest_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tumbler_gpio_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tumbler_cleanup(struct snd_pmac *chip)
{
	struct pmac_tumbler *mix = chip->mixer_data;
	if (! mix)
		return;

	if (mix->headphone_irq >= 0)
		free_irq(mix->headphone_irq, chip);
	if (mix->lineout_irq >= 0)
		free_irq(mix->lineout_irq, chip);
	tumbler_gpio_free(&mix->audio_reset);
	tumbler_gpio_free(&mix->amp_mute);
	tumbler_gpio_free(&mix->hp_mute);
	tumbler_gpio_free(&mix->hp_detect);
	snd_pmac_keywest_cleanup(&mix->i2c);
	kfree(mix);
	chip->mixer_data = NULL;
}