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
struct snd_kcontrol {int dummy; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;
struct snd_at73c213 {TYPE_1__* pcm; struct snd_card* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * snd_at73c213_controls ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ctl_find_numid (struct snd_card*,int) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_at73c213*) ; 
 int /*<<< orphan*/  snd_ctl_remove (struct snd_card*,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_at73c213_mixer(struct snd_at73c213 *chip)
{
	struct snd_card *card;
	int errval, idx;

	if (chip == NULL || chip->pcm == NULL)
		return -EINVAL;

	card = chip->card;

	strcpy(card->mixername, chip->pcm->name);

	for (idx = 0; idx < ARRAY_SIZE(snd_at73c213_controls); idx++) {
		errval = snd_ctl_add(card,
				snd_ctl_new1(&snd_at73c213_controls[idx],
					chip));
		if (errval < 0)
			goto cleanup;
	}

	return 0;

cleanup:
	for (idx = 1; idx < ARRAY_SIZE(snd_at73c213_controls) + 1; idx++) {
		struct snd_kcontrol *kctl;
		kctl = snd_ctl_find_numid(card, idx);
		if (kctl)
			snd_ctl_remove(card, kctl);
	}
	return errval;
}