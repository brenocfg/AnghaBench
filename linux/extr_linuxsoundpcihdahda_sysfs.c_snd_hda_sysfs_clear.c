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
struct hda_codec {int dummy; } ;

/* Variables and functions */

void snd_hda_sysfs_clear(struct hda_codec *codec)
{
#ifdef CONFIG_SND_HDA_RECONFIG
	struct hda_hint *hint;
	int i;

	/* clear init verbs */
	snd_array_free(&codec->init_verbs);
	/* clear hints */
	snd_array_for_each(&codec->hints, i, hint) {
		kfree(hint->key); /* we don't need to free hint->val */
	}
	snd_array_free(&codec->hints);
	snd_array_free(&codec->user_pins);
#endif
}