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
struct snd_pcm_substream {int dummy; } ;
struct cmipci {int dig_pcm_status; int /*<<< orphan*/ * channel; scalar_t__ can_ac3_hw; } ;

/* Variables and functions */
 size_t CM_CH_PLAY ; 
 int IEC958_AES0_NONAUDIO ; 
 int setup_spdif_playback (struct cmipci*,struct snd_pcm_substream*,int,int) ; 
 int snd_cmipci_pcm_prepare (struct cmipci*,int /*<<< orphan*/ *,struct snd_pcm_substream*) ; 
 struct cmipci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cmipci_playback_spdif_prepare(struct snd_pcm_substream *substream)
{
	struct cmipci *cm = snd_pcm_substream_chip(substream);
	int err, do_ac3;

	if (cm->can_ac3_hw) 
		do_ac3 = cm->dig_pcm_status & IEC958_AES0_NONAUDIO;
	else
		do_ac3 = 1; /* doesn't matter */
	if ((err = setup_spdif_playback(cm, substream, 1, do_ac3)) < 0)
		return err;
	return snd_cmipci_pcm_prepare(cm, &cm->channel[CM_CH_PLAY], substream);
}