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
struct snd_pmac {int /*<<< orphan*/  card; } ;
struct snd_kcontrol {int /*<<< orphan*/  id; } ;
struct pmac_gpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int check_audio_gpio (struct pmac_gpio*) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_audio_gpio (struct pmac_gpio*,int) ; 

__attribute__((used)) static void check_mute(struct snd_pmac *chip, struct pmac_gpio *gp, int val, int do_notify,
		       struct snd_kcontrol *sw)
{
	if (check_audio_gpio(gp) != val) {
		write_audio_gpio(gp, val);
		if (do_notify)
			snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &sw->id);
	}
}