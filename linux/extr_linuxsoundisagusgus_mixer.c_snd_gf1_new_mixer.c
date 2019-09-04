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
struct snd_gus_card {scalar_t__ ess_flag; scalar_t__ ics_flag; struct snd_card* card; } ;
struct snd_card {char* mixername; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_component_add (struct snd_card*,char*) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_gus_card*) ; 
 int /*<<< orphan*/ * snd_gf1_controls ; 
 int /*<<< orphan*/ * snd_ics_controls ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int snd_gf1_new_mixer(struct snd_gus_card * gus)
{
	struct snd_card *card;
	unsigned int idx, max;
	int err;

	if (snd_BUG_ON(!gus))
		return -EINVAL;
	card = gus->card;
	if (snd_BUG_ON(!card))
		return -EINVAL;

	if (gus->ics_flag)
		snd_component_add(card, "ICS2101");
	if (card->mixername[0] == '\0') {
		strcpy(card->mixername, gus->ics_flag ? "GF1,ICS2101" : "GF1");
	} else {
		if (gus->ics_flag)
			strcat(card->mixername, ",ICS2101");
		strcat(card->mixername, ",GF1");
	}

	if (!gus->ics_flag) {
		max = gus->ess_flag ? 1 : ARRAY_SIZE(snd_gf1_controls);
		for (idx = 0; idx < max; idx++) {
			if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_gf1_controls[idx], gus))) < 0)
				return err;
		}
	} else {
		for (idx = 0; idx < ARRAY_SIZE(snd_ics_controls); idx++) {
			if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_ics_controls[idx], gus))) < 0)
				return err;
		}
	}
	return 0;
}