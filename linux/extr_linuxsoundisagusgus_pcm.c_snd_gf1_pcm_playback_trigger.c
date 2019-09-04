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
struct snd_pcm_runtime {struct gus_pcm_private* private_data; } ;
struct snd_gus_card {int dummy; } ;
struct gus_pcm_private {TYPE_1__** pvoices; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_GF1_PCM_PFLG_ACTIVE ; 
 int SNDRV_PCM_TRIGGER_START ; 
 int SNDRV_PCM_TRIGGER_STOP ; 
 int /*<<< orphan*/  snd_gf1_pcm_trigger_up (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_gf1_stop_voices (struct snd_gus_card*,int,int) ; 
 struct snd_gus_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_gf1_pcm_playback_trigger(struct snd_pcm_substream *substream,
					int cmd)
{
	struct snd_gus_card *gus = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct gus_pcm_private *pcmp = runtime->private_data;
	int voice;

	if (cmd == SNDRV_PCM_TRIGGER_START) {
		snd_gf1_pcm_trigger_up(substream);
	} else if (cmd == SNDRV_PCM_TRIGGER_STOP) {
		spin_lock(&pcmp->lock);
		pcmp->flags &= ~SNDRV_GF1_PCM_PFLG_ACTIVE;
		spin_unlock(&pcmp->lock);
		voice = pcmp->pvoices[0]->number;
		snd_gf1_stop_voices(gus, voice, voice);
		if (pcmp->pvoices[1]) {
			voice = pcmp->pvoices[1]->number;
			snd_gf1_stop_voices(gus, voice, voice);
		}
	} else {
		return -EINVAL;
	}
	return 0;
}