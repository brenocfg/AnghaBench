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
struct snd_pmac {int /*<<< orphan*/  card; } ;
struct snd_kcontrol_new {int dummy; } ;

/* Variables and functions */
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_pmac*) ; 

__attribute__((used)) static int build_mixers(struct snd_pmac *chip, int nums,
			struct snd_kcontrol_new *mixers)
{
	int i, err;

	for (i = 0; i < nums; i++) {
		err = snd_ctl_add(chip->card, snd_ctl_new1(&mixers[i], chip));
		if (err < 0)
			return err;
	}
	return 0;
}