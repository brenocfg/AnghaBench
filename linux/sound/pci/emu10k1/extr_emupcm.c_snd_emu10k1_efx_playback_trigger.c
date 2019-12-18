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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_emu10k1_pcm* private_data; } ;
struct snd_emu10k1_pcm {int running; int /*<<< orphan*/  extra; int /*<<< orphan*/ * voices; } ;
struct snd_emu10k1 {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/ * efx_pcm_mixer; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_EFX_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  snd_emu10k1_playback_invalidate_cache (struct snd_emu10k1*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_playback_prepare_voice (struct snd_emu10k1*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_emu10k1_playback_stop_voice (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_playback_trigger_voice (struct snd_emu10k1*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_emu10k1_efx_playback_trigger(struct snd_pcm_substream *substream,
				        int cmd)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_emu10k1_pcm *epcm = runtime->private_data;
	int i;
	int result = 0;

	spin_lock(&emu->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		/* prepare voices */
		for (i = 0; i < NUM_EFX_PLAYBACK; i++) {	
			snd_emu10k1_playback_invalidate_cache(emu, 0, epcm->voices[i]);
		}
		snd_emu10k1_playback_invalidate_cache(emu, 1, epcm->extra);

		/* fall through */
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		snd_emu10k1_playback_prepare_voice(emu, epcm->extra, 1, 1, NULL);
		snd_emu10k1_playback_prepare_voice(emu, epcm->voices[0], 0, 0,
						   &emu->efx_pcm_mixer[0]);
		for (i = 1; i < NUM_EFX_PLAYBACK; i++)
			snd_emu10k1_playback_prepare_voice(emu, epcm->voices[i], 0, 0,
							   &emu->efx_pcm_mixer[i]);
		snd_emu10k1_playback_trigger_voice(emu, epcm->voices[0], 0, 0);
		snd_emu10k1_playback_trigger_voice(emu, epcm->extra, 1, 1);
		for (i = 1; i < NUM_EFX_PLAYBACK; i++)
			snd_emu10k1_playback_trigger_voice(emu, epcm->voices[i], 0, 0);
		epcm->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		epcm->running = 0;
		for (i = 0; i < NUM_EFX_PLAYBACK; i++) {	
			snd_emu10k1_playback_stop_voice(emu, epcm->voices[i]);
		}
		snd_emu10k1_playback_stop_voice(emu, epcm->extra);
		break;
	default:
		result = -EINVAL;
		break;
	}
	spin_unlock(&emu->reg_lock);
	return result;
}