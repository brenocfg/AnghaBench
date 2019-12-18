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
struct snd_pcsp {struct snd_card* card; } ;
struct snd_kcontrol_new {int dummy; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_pcsp*) ; 

__attribute__((used)) static int snd_pcsp_ctls_add(struct snd_pcsp *chip,
			     struct snd_kcontrol_new *ctls, int num)
{
	int i, err;
	struct snd_card *card = chip->card;
	for (i = 0; i < num; i++) {
		err = snd_ctl_add(card, snd_ctl_new1(ctls + i, chip));
		if (err < 0)
			return err;
	}
	return 0;
}