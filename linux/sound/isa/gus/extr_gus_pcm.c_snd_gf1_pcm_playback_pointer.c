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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; struct gus_pcm_private* private_data; } ;
struct snd_gus_card {int /*<<< orphan*/  reg_lock; } ;
struct gus_pcm_private {int flags; int memory; TYPE_1__** pvoices; } ;
typedef  unsigned int snd_pcm_uframes_t ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int SNDRV_GF1_PCM_PFLG_ACTIVE ; 
 int /*<<< orphan*/  SNDRV_GF1_VA_CURRENT ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_ADDRESS_CONTROL ; 
 unsigned int bytes_to_frames (struct snd_pcm_runtime*,unsigned int) ; 
 unsigned char snd_gf1_read8 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int snd_gf1_read_addr (struct snd_gus_card*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  snd_gf1_select_voice (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 struct snd_gus_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_gf1_pcm_playback_pointer(struct snd_pcm_substream *substream)
{
	struct snd_gus_card *gus = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct gus_pcm_private *pcmp = runtime->private_data;
	unsigned int pos;
	unsigned char voice_ctrl;

	pos = 0;
	spin_lock(&gus->reg_lock);
	if (pcmp->flags & SNDRV_GF1_PCM_PFLG_ACTIVE) {
		snd_gf1_select_voice(gus, pcmp->pvoices[0]->number);
		voice_ctrl = snd_gf1_read8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL);
		pos = (snd_gf1_read_addr(gus, SNDRV_GF1_VA_CURRENT, voice_ctrl & 4) >> 4) - pcmp->memory;
		if (substream->runtime->channels > 1)
			pos <<= 1;
		pos = bytes_to_frames(runtime, pos);
	}
	spin_unlock(&gus->reg_lock);
	return pos;
}