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
struct snd_sgio2audio {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  sgio2audio_ctrl_cd ; 
 int /*<<< orphan*/  sgio2audio_ctrl_line ; 
 int /*<<< orphan*/  sgio2audio_ctrl_mic ; 
 int /*<<< orphan*/  sgio2audio_ctrl_pcm0 ; 
 int /*<<< orphan*/  sgio2audio_ctrl_pcm1 ; 
 int /*<<< orphan*/  sgio2audio_ctrl_reclevel ; 
 int /*<<< orphan*/  sgio2audio_ctrl_recsource ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_sgio2audio*) ; 

__attribute__((used)) static int snd_sgio2audio_new_mixer(struct snd_sgio2audio *chip)
{
	int err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_pcm0, chip));
	if (err < 0)
		return err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_pcm1, chip));
	if (err < 0)
		return err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_reclevel, chip));
	if (err < 0)
		return err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_recsource, chip));
	if (err < 0)
		return err;
	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_line, chip));
	if (err < 0)
		return err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_cd, chip));
	if (err < 0)
		return err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_mic, chip));
	if (err < 0)
		return err;

	return 0;
}