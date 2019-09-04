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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct snd_dummy {int iobox; struct snd_kcontrol* cd_switch_ctl; struct snd_kcontrol* cd_volume_ctl; int /*<<< orphan*/  mixer_lock; struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_dummy*) ; 
 int /*<<< orphan*/ * snd_dummy_controls ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_card_dummy_new_mixer(struct snd_dummy *dummy)
{
	struct snd_card *card = dummy->card;
	struct snd_kcontrol *kcontrol;
	unsigned int idx;
	int err;

	spin_lock_init(&dummy->mixer_lock);
	strcpy(card->mixername, "Dummy Mixer");
	dummy->iobox = 1;

	for (idx = 0; idx < ARRAY_SIZE(snd_dummy_controls); idx++) {
		kcontrol = snd_ctl_new1(&snd_dummy_controls[idx], dummy);
		err = snd_ctl_add(card, kcontrol);
		if (err < 0)
			return err;
		if (!strcmp(kcontrol->id.name, "CD Volume"))
			dummy->cd_volume_ctl = kcontrol;
		else if (!strcmp(kcontrol->id.name, "CD Capture Switch"))
			dummy->cd_switch_ctl = kcontrol;

	}
	return 0;
}