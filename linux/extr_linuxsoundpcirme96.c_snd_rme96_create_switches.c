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
struct snd_card {int dummy; } ;
struct rme96 {struct snd_kcontrol* spdif_ctl; } ;

/* Variables and functions */
 scalar_t__ RME96_HAS_ANALOG_OUT (struct rme96*) ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct rme96*) ; 
 int /*<<< orphan*/ * snd_rme96_controls ; 

__attribute__((used)) static int
snd_rme96_create_switches(struct snd_card *card,
			  struct rme96 *rme96)
{
	int idx, err;
	struct snd_kcontrol *kctl;

	for (idx = 0; idx < 7; idx++) {
		if ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_rme96_controls[idx], rme96))) < 0)
			return err;
		if (idx == 1)	/* IEC958 (S/PDIF) Stream */
			rme96->spdif_ctl = kctl;
	}

	if (RME96_HAS_ANALOG_OUT(rme96)) {
		for (idx = 7; idx < 10; idx++)
			if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_rme96_controls[idx], rme96))) < 0)
				return err;
	}
	
	return 0;
}