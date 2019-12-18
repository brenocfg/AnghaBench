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
struct rme32 {struct snd_kcontrol* spdif_ctl; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct rme32*) ; 
 int /*<<< orphan*/ * snd_rme32_controls ; 

__attribute__((used)) static int snd_rme32_create_switches(struct snd_card *card, struct rme32 * rme32)
{
	int idx, err;
	struct snd_kcontrol *kctl;

	for (idx = 0; idx < (int)ARRAY_SIZE(snd_rme32_controls); idx++) {
		if ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_rme32_controls[idx], rme32))) < 0)
			return err;
		if (idx == 1)	/* IEC958 (S/PDIF) Stream */
			rme32->spdif_ctl = kctl;
	}

	return 0;
}