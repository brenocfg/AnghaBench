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
struct snd_pcm_substream {size_t number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_emu10k1_pcm* private_data; } ;
struct snd_emu10k1_pcm_mixer {int dummy; } ;
struct snd_emu10k1_pcm {int running; int /*<<< orphan*/  extra; int /*<<< orphan*/ * voices; } ;
struct snd_emu10k1 {int /*<<< orphan*/  reg_lock; struct snd_emu10k1_pcm_mixer* pcm_mixer; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  snd_emu10k1_playback_invalidate_cache (struct snd_emu10k1*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_playback_mangle_extra (struct snd_emu10k1*,struct snd_emu10k1_pcm*,struct snd_pcm_substream*,struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_emu10k1_playback_prepare_voice (struct snd_emu10k1*,int /*<<< orphan*/ ,int,int,struct snd_emu10k1_pcm_mixer*) ; 
 int /*<<< orphan*/  snd_emu10k1_playback_stop_voice (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_playback_trigger_voice (struct snd_emu10k1*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_emu10k1_playback_trigger(struct snd_pcm_substream *substream,
				        int cmd)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_emu10k1_pcm *epcm = runtime->private_data;
	struct snd_emu10k1_pcm_mixer *mix;
	int result = 0;

	/*
	dev_dbg(emu->card->dev,
		"trigger - emu10k1 = 0x%x, cmd = %i, pointer = %i\n",
	       (int)emu, cmd, substream->ops->pointer(substream))
	*/
	spin_lock(&emu->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		snd_emu10k1_playback_invalidate_cache(emu, 1, epcm->extra);	/* do we need this? */
		snd_emu10k1_playback_invalidate_cache(emu, 0, epcm->voices[0]);
		/* fall through */
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		if (cmd == SNDRV_PCM_TRIGGER_PAUSE_RELEASE)
			snd_emu10k1_playback_mangle_extra(emu, epcm, substream, runtime);
		mix = &emu->pcm_mixer[substream->number];
		snd_emu10k1_playback_prepare_voice(emu, epcm->voices[0], 1, 0, mix);
		snd_emu10k1_playback_prepare_voice(emu, epcm->voices[1], 0, 0, mix);
		snd_emu10k1_playback_prepare_voice(emu, epcm->extra, 1, 1, NULL);
		snd_emu10k1_playback_trigger_voice(emu, epcm->voices[0], 1, 0);
		snd_emu10k1_playback_trigger_voice(emu, epcm->voices[1], 0, 0);
		snd_emu10k1_playback_trigger_voice(emu, epcm->extra, 1, 1);
		epcm->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		epcm->running = 0;
		snd_emu10k1_playback_stop_voice(emu, epcm->voices[0]);
		snd_emu10k1_playback_stop_voice(emu, epcm->voices[1]);
		snd_emu10k1_playback_stop_voice(emu, epcm->extra);
		break;
	default:
		result = -EINVAL;
		break;
	}
	spin_unlock(&emu->reg_lock);
	return result;
}