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
struct snd_cs4231 {TYPE_1__* pcm; } ;
struct snd_card {int /*<<< orphan*/  mixername; struct snd_cs4231* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/ * snd_cs4231_controls ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_cs4231*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cs4231_mixer(struct snd_card *card)
{
	struct snd_cs4231 *chip = card->private_data;
	int err, idx;

	if (snd_BUG_ON(!chip || !chip->pcm))
		return -EINVAL;

	strcpy(card->mixername, chip->pcm->name);

	for (idx = 0; idx < ARRAY_SIZE(snd_cs4231_controls); idx++) {
		err = snd_ctl_add(card,
				 snd_ctl_new1(&snd_cs4231_controls[idx], chip));
		if (err < 0)
			return err;
	}
	return 0;
}