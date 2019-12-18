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
struct snd_harmony {struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;

/* Variables and functions */
 int EINVAL ; 
 int HARMONY_CONTROLS ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_harmony*) ; 
 int /*<<< orphan*/ * snd_harmony_controls ; 
 int /*<<< orphan*/  snd_harmony_mixer_reset (struct snd_harmony*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
snd_harmony_mixer_init(struct snd_harmony *h)
{
	struct snd_card *card;
	int idx, err;

	if (snd_BUG_ON(!h))
		return -EINVAL;
	card = h->card;
	strcpy(card->mixername, "Harmony Gain control interface");

	for (idx = 0; idx < HARMONY_CONTROLS; idx++) {
		err = snd_ctl_add(card, 
				  snd_ctl_new1(&snd_harmony_controls[idx], h));
		if (err < 0)
			return err;
	}
	
	snd_harmony_mixer_reset(h);

	return 0;
}