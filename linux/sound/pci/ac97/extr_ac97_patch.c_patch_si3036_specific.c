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
struct snd_ac97 {TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * snd_ac97_controls_si3036 ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_ac97*) ; 

__attribute__((used)) static int patch_si3036_specific(struct snd_ac97 * ac97)
{
	int idx, err;
	for (idx = 0; idx < ARRAY_SIZE(snd_ac97_controls_si3036); idx++)
		if ((err = snd_ctl_add(ac97->bus->card, snd_ctl_new1(&snd_ac97_controls_si3036[idx], ac97))) < 0)
			return err;
	return 0;
}