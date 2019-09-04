#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcxhr {int /*<<< orphan*/  card; TYPE_1__* mgr; } ;
struct TYPE_2__ {int /*<<< orphan*/  board_has_mic; } ;

/* Variables and functions */
 int /*<<< orphan*/  hr222_control_mic_boost ; 
 int /*<<< orphan*/  hr222_control_mic_level ; 
 int /*<<< orphan*/  hr222_phantom_power_switch ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_pcxhr*) ; 

int hr222_add_mic_controls(struct snd_pcxhr *chip)
{
	int err;
	if (!chip->mgr->board_has_mic)
		return 0;

	/* controls */
	err = snd_ctl_add(chip->card, snd_ctl_new1(&hr222_control_mic_level,
						   chip));
	if (err < 0)
		return err;

	err = snd_ctl_add(chip->card, snd_ctl_new1(&hr222_control_mic_boost,
						   chip));
	if (err < 0)
		return err;

	err = snd_ctl_add(chip->card, snd_ctl_new1(&hr222_phantom_power_switch,
						   chip));
	return err;
}