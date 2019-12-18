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
struct snd_kcontrol {int dummy; } ;
struct snd_cs46xx {scalar_t__ in_suspend; struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hercules_init (struct snd_cs46xx*) ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_cs46xx*) ; 
 int /*<<< orphan*/ * snd_hercules_controls ; 

__attribute__((used)) static void hercules_mixer_init (struct snd_cs46xx *chip)
{
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	unsigned int idx;
	int err;
	struct snd_card *card = chip->card;
#endif

	/* set EGPIO to default */
	hercules_init(chip);

	dev_dbg(chip->card->dev, "initializing Hercules mixer\n");

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	if (chip->in_suspend)
		return;

	for (idx = 0 ; idx < ARRAY_SIZE(snd_hercules_controls); idx++) {
		struct snd_kcontrol *kctl;

		kctl = snd_ctl_new1(&snd_hercules_controls[idx], chip);
		if ((err = snd_ctl_add(card, kctl)) < 0) {
			dev_err(card->dev,
				"failed to initialize Hercules mixer (%d)\n",
				err);
			break;
		}
	}
#endif
}