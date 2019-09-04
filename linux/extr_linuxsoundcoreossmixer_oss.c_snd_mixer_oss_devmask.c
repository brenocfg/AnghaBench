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
struct snd_mixer_oss_slot {scalar_t__ put_recsrc; scalar_t__ put_volume; } ;
struct snd_mixer_oss_file {struct snd_mixer_oss* mixer; } ;
struct snd_mixer_oss {struct snd_mixer_oss_slot* slots; } ;

/* Variables and functions */
 int EIO ; 

__attribute__((used)) static int snd_mixer_oss_devmask(struct snd_mixer_oss_file *fmixer)
{
	struct snd_mixer_oss *mixer = fmixer->mixer;
	struct snd_mixer_oss_slot *pslot;
	int result = 0, chn;

	if (mixer == NULL)
		return -EIO;
	for (chn = 0; chn < 31; chn++) {
		pslot = &mixer->slots[chn];
		if (pslot->put_volume || pslot->put_recsrc)
			result |= 1 << chn;
	}
	return result;
}