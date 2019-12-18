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
struct snd_card {int /*<<< orphan*/  shortname; int /*<<< orphan*/  mixername; } ;
struct snd_amd7930 {struct snd_card* card; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * amd7930_controls ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_amd7930*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_amd7930_mixer(struct snd_amd7930 *amd)
{
	struct snd_card *card;
	int idx, err;

	if (snd_BUG_ON(!amd || !amd->card))
		return -EINVAL;

	card = amd->card;
	strcpy(card->mixername, card->shortname);

	for (idx = 0; idx < ARRAY_SIZE(amd7930_controls); idx++) {
		if ((err = snd_ctl_add(card,
				       snd_ctl_new1(&amd7930_controls[idx], amd))) < 0)
			return err;
	}

	return 0;
}