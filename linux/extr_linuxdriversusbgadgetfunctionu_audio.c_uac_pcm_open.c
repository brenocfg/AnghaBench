#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uac_params {int p_ssize; int c_ssize; int p_srate; int c_srate; int p_chmask; int c_chmask; } ;
struct TYPE_5__ {int max_psize; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int max_psize; int /*<<< orphan*/  lock; } ;
struct snd_uac_chip {TYPE_2__ c_prm; TYPE_1__ p_prm; scalar_t__ p_residue; struct g_audio* audio_dev; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct TYPE_6__ {int rate_min; int period_bytes_min; int periods_min; int rate_max; void* channels_min; void* channels_max; void* formats; } ;
struct snd_pcm_runtime {TYPE_3__ hw; } ;
struct g_audio {struct uac_params params; } ;

/* Variables and functions */
 void* SNDRV_PCM_FMTBIT_S16_LE ; 
 void* SNDRV_PCM_FMTBIT_S24_3LE ; 
 void* SNDRV_PCM_FMTBIT_S32_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 void* num_channels (int) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_uac_chip* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_3__ uac_pcm_hardware ; 

__attribute__((used)) static int uac_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_uac_chip *uac = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct g_audio *audio_dev;
	struct uac_params *params;
	int p_ssize, c_ssize;
	int p_srate, c_srate;
	int p_chmask, c_chmask;

	audio_dev = uac->audio_dev;
	params = &audio_dev->params;
	p_ssize = params->p_ssize;
	c_ssize = params->c_ssize;
	p_srate = params->p_srate;
	c_srate = params->c_srate;
	p_chmask = params->p_chmask;
	c_chmask = params->c_chmask;
	uac->p_residue = 0;

	runtime->hw = uac_pcm_hardware;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		spin_lock_init(&uac->p_prm.lock);
		runtime->hw.rate_min = p_srate;
		switch (p_ssize) {
		case 3:
			runtime->hw.formats = SNDRV_PCM_FMTBIT_S24_3LE;
			break;
		case 4:
			runtime->hw.formats = SNDRV_PCM_FMTBIT_S32_LE;
			break;
		default:
			runtime->hw.formats = SNDRV_PCM_FMTBIT_S16_LE;
			break;
		}
		runtime->hw.channels_min = num_channels(p_chmask);
		runtime->hw.period_bytes_min = 2 * uac->p_prm.max_psize
						/ runtime->hw.periods_min;
	} else {
		spin_lock_init(&uac->c_prm.lock);
		runtime->hw.rate_min = c_srate;
		switch (c_ssize) {
		case 3:
			runtime->hw.formats = SNDRV_PCM_FMTBIT_S24_3LE;
			break;
		case 4:
			runtime->hw.formats = SNDRV_PCM_FMTBIT_S32_LE;
			break;
		default:
			runtime->hw.formats = SNDRV_PCM_FMTBIT_S16_LE;
			break;
		}
		runtime->hw.channels_min = num_channels(c_chmask);
		runtime->hw.period_bytes_min = 2 * uac->c_prm.max_psize
						/ runtime->hw.periods_min;
	}

	runtime->hw.rate_max = runtime->hw.rate_min;
	runtime->hw.channels_max = runtime->hw.channels_min;

	snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS);

	return 0;
}