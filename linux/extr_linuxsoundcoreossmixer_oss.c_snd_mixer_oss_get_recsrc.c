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
struct snd_mixer_oss_slot {int /*<<< orphan*/  (* get_recsrc ) (struct snd_mixer_oss_file*,struct snd_mixer_oss_slot*,int*) ;} ;
struct snd_mixer_oss_file {struct snd_mixer_oss* mixer; } ;
struct snd_mixer_oss {int (* get_recsrc ) (struct snd_mixer_oss_file*,unsigned int*) ;int oss_recsrc; struct snd_mixer_oss_slot* slots; scalar_t__ put_recsrc; } ;

/* Variables and functions */
 int EIO ; 
 int stub1 (struct snd_mixer_oss_file*,unsigned int*) ; 
 int /*<<< orphan*/  stub2 (struct snd_mixer_oss_file*,struct snd_mixer_oss_slot*,int*) ; 

__attribute__((used)) static int snd_mixer_oss_get_recsrc(struct snd_mixer_oss_file *fmixer)
{
	struct snd_mixer_oss *mixer = fmixer->mixer;
	int result = 0;

	if (mixer == NULL)
		return -EIO;
	if (mixer->put_recsrc && mixer->get_recsrc) {	/* exclusive */
		int err;
		unsigned int index;
		if ((err = mixer->get_recsrc(fmixer, &index)) < 0)
			return err;
		result = 1 << index;
	} else {
		struct snd_mixer_oss_slot *pslot;
		int chn;
		for (chn = 0; chn < 31; chn++) {
			pslot = &mixer->slots[chn];
			if (pslot->get_recsrc) {
				int active = 0;
				pslot->get_recsrc(fmixer, pslot, &active);
				if (active)
					result |= 1 << chn;
			}
		}
	}
	return mixer->oss_recsrc = result;
}