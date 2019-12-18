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
struct snd_emu10k1 {struct snd_card* card; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * p16v_mixer_controls ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_emu10k1*) ; 

int snd_p16v_mixer(struct snd_emu10k1 *emu)
{
	int i, err;
        struct snd_card *card = emu->card;

	for (i = 0; i < ARRAY_SIZE(p16v_mixer_controls); i++) {
		if ((err = snd_ctl_add(card, snd_ctl_new1(&p16v_mixer_controls[i],
							  emu))) < 0)
			return err;
	}
        return 0;
}