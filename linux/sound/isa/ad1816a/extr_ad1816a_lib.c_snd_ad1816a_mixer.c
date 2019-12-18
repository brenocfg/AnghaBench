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
struct snd_card {int /*<<< orphan*/  mixername; } ;
struct snd_ad1816a {struct snd_card* card; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_ad1816a_chip_id (struct snd_ad1816a*) ; 
 int /*<<< orphan*/ * snd_ad1816a_controls ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_ad1816a*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_ad1816a_mixer(struct snd_ad1816a *chip)
{
	struct snd_card *card;
	unsigned int idx;
	int err;

	if (snd_BUG_ON(!chip || !chip->card))
		return -EINVAL;

	card = chip->card;

	strcpy(card->mixername, snd_ad1816a_chip_id(chip));

	for (idx = 0; idx < ARRAY_SIZE(snd_ad1816a_controls); idx++) {
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_ad1816a_controls[idx], chip))) < 0)
			return err;
	}
	return 0;
}