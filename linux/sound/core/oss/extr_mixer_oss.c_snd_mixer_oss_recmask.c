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
struct snd_mixer_oss_slot {scalar_t__ put_recsrc; } ;
struct snd_mixer_oss_file {struct snd_mixer_oss* mixer; } ;
struct snd_mixer_oss {int mask_recsrc; struct snd_mixer_oss_slot* slots; scalar_t__ get_recsrc; scalar_t__ put_recsrc; } ;

/* Variables and functions */
 int EIO ; 

__attribute__((used)) static int snd_mixer_oss_recmask(struct snd_mixer_oss_file *fmixer)
{
	struct snd_mixer_oss *mixer = fmixer->mixer;
	int result = 0;

	if (mixer == NULL)
		return -EIO;
	if (mixer->put_recsrc && mixer->get_recsrc) {	/* exclusive */
		result = mixer->mask_recsrc;
	} else {
		struct snd_mixer_oss_slot *pslot;
		int chn;
		for (chn = 0; chn < 31; chn++) {
			pslot = &mixer->slots[chn];
			if (pslot->put_recsrc)
				result |= 1 << chn;
		}
	}
	return result;
}