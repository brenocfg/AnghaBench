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
struct pmac_tumbler {int /*<<< orphan*/  audio_reset; int /*<<< orphan*/  amp_mute; int /*<<< orphan*/  hp_mute; scalar_t__ anded_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  write_audio_gpio (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tumbler_reset_audio(struct snd_pmac *chip)
{
	struct pmac_tumbler *mix = chip->mixer_data;

	if (mix->anded_reset) {
		DBG("(I) codec anded reset !\n");
		write_audio_gpio(&mix->hp_mute, 0);
		write_audio_gpio(&mix->amp_mute, 0);
		msleep(200);
		write_audio_gpio(&mix->hp_mute, 1);
		write_audio_gpio(&mix->amp_mute, 1);
		msleep(100);
		write_audio_gpio(&mix->hp_mute, 0);
		write_audio_gpio(&mix->amp_mute, 0);
		msleep(100);
	} else {
		DBG("(I) codec normal reset !\n");

		write_audio_gpio(&mix->audio_reset, 0);
		msleep(200);
		write_audio_gpio(&mix->audio_reset, 1);
		msleep(100);
		write_audio_gpio(&mix->audio_reset, 0);
		msleep(100);
	}
}