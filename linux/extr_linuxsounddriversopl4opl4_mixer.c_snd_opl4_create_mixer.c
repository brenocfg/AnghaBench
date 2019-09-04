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
struct snd_opl4 {struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;

/* Variables and functions */
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_opl4*) ; 
 int /*<<< orphan*/ * snd_opl4_controls ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 

int snd_opl4_create_mixer(struct snd_opl4 *opl4)
{
	struct snd_card *card = opl4->card;
	int i, err;

	strcat(card->mixername, ",OPL4");

	for (i = 0; i < 2; ++i) {
		err = snd_ctl_add(card, snd_ctl_new1(&snd_opl4_controls[i], opl4));
		if (err < 0)
			return err;
	}
	return 0;
}