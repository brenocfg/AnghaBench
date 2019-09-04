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
struct snd_card {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pisnd_ctl ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pisnd_ctl_init(struct snd_card *card)
{
	int err, i;

	for (i = 0; i < ARRAY_SIZE(pisnd_ctl); ++i) {
		err = snd_ctl_add(card, snd_ctl_new1(&pisnd_ctl[i], NULL));
		if (err < 0)
			return err;
	}

	return 0;
}