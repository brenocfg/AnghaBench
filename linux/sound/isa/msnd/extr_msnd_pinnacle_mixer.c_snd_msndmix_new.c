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
struct snd_msnd {int /*<<< orphan*/  mixer_lock; } ;
struct snd_card {int /*<<< orphan*/  mixername; struct snd_msnd* private_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (scalar_t__,struct snd_msnd*) ; 
 scalar_t__ snd_msnd_controls ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_msndmix_new(struct snd_card *card)
{
	struct snd_msnd *chip = card->private_data;
	unsigned int idx;
	int err;

	if (snd_BUG_ON(!chip))
		return -EINVAL;
	spin_lock_init(&chip->mixer_lock);
	strcpy(card->mixername, "MSND Pinnacle Mixer");

	for (idx = 0; idx < ARRAY_SIZE(snd_msnd_controls); idx++) {
		err = snd_ctl_add(card,
				  snd_ctl_new1(snd_msnd_controls + idx, chip));
		if (err < 0)
			return err;
	}

	return 0;
}