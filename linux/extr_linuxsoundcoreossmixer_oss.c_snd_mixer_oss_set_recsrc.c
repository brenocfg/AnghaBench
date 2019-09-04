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
struct snd_mixer_oss_slot {int /*<<< orphan*/  (* get_recsrc ) (struct snd_mixer_oss_file*,struct snd_mixer_oss_slot*,int*) ;int /*<<< orphan*/  (* put_recsrc ) (struct snd_mixer_oss_file*,struct snd_mixer_oss_slot*,int) ;} ;
struct snd_mixer_oss_file {struct snd_mixer_oss* mixer; } ;
struct snd_mixer_oss {int oss_recsrc; struct snd_mixer_oss_slot* slots; int /*<<< orphan*/  (* get_recsrc ) (struct snd_mixer_oss_file*,unsigned int*) ;int /*<<< orphan*/  (* put_recsrc ) (struct snd_mixer_oss_file*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ffz (int) ; 
 int /*<<< orphan*/  stub1 (struct snd_mixer_oss_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_mixer_oss_file*,unsigned int*) ; 
 int /*<<< orphan*/  stub3 (struct snd_mixer_oss_file*,struct snd_mixer_oss_slot*,int) ; 
 int /*<<< orphan*/  stub4 (struct snd_mixer_oss_file*,struct snd_mixer_oss_slot*,int*) ; 

__attribute__((used)) static int snd_mixer_oss_set_recsrc(struct snd_mixer_oss_file *fmixer, int recsrc)
{
	struct snd_mixer_oss *mixer = fmixer->mixer;
	struct snd_mixer_oss_slot *pslot;
	int chn, active;
	unsigned int index;
	int result = 0;

	if (mixer == NULL)
		return -EIO;
	if (mixer->get_recsrc && mixer->put_recsrc) {	/* exclusive input */
		if (recsrc & ~mixer->oss_recsrc)
			recsrc &= ~mixer->oss_recsrc;
		mixer->put_recsrc(fmixer, ffz(~recsrc));
		mixer->get_recsrc(fmixer, &index);
		result = 1 << index;
	}
	for (chn = 0; chn < 31; chn++) {
		pslot = &mixer->slots[chn];
		if (pslot->put_recsrc) {
			active = (recsrc & (1 << chn)) ? 1 : 0;
			pslot->put_recsrc(fmixer, pslot, active);
		}
	}
	if (! result) {
		for (chn = 0; chn < 31; chn++) {
			pslot = &mixer->slots[chn];
			if (pslot->get_recsrc) {
				active = 0;
				pslot->get_recsrc(fmixer, pslot, &active);
				if (active)
					result |= 1 << chn;
			}
		}
	}
	return result;
}