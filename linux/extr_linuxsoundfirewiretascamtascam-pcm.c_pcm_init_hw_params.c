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
struct amdtp_stream {int dummy; } ;
struct snd_tscm {TYPE_1__* spec; struct amdtp_stream rx_stream; struct amdtp_stream tx_stream; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_hardware {unsigned int channels_min; unsigned int channels_max; int rates; void* formats; } ;
struct snd_pcm_runtime {struct snd_pcm_hardware hw; } ;
struct TYPE_2__ {unsigned int pcm_capture_analog_channels; unsigned int pcm_playback_analog_channels; scalar_t__ has_spdif; scalar_t__ has_adat; } ;

/* Variables and functions */
 void* SNDRV_PCM_FMTBIT_S32 ; 
 int SNDRV_PCM_RATE_44100 ; 
 int SNDRV_PCM_RATE_48000 ; 
 int SNDRV_PCM_RATE_88200 ; 
 int SNDRV_PCM_RATE_96000 ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int amdtp_tscm_add_pcm_hw_constraints (struct amdtp_stream*,struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_pcm_limit_hw_rates (struct snd_pcm_runtime*) ; 

__attribute__((used)) static int pcm_init_hw_params(struct snd_tscm *tscm,
			      struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_pcm_hardware *hw = &runtime->hw;
	struct amdtp_stream *stream;
	unsigned int pcm_channels;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		runtime->hw.formats = SNDRV_PCM_FMTBIT_S32;
		stream = &tscm->tx_stream;
		pcm_channels = tscm->spec->pcm_capture_analog_channels;
	} else {
		runtime->hw.formats = SNDRV_PCM_FMTBIT_S32;
		stream = &tscm->rx_stream;
		pcm_channels = tscm->spec->pcm_playback_analog_channels;
	}

	if (tscm->spec->has_adat)
		pcm_channels += 8;
	if (tscm->spec->has_spdif)
		pcm_channels += 2;
	runtime->hw.channels_min = runtime->hw.channels_max = pcm_channels;

	hw->rates = SNDRV_PCM_RATE_44100 |
		    SNDRV_PCM_RATE_48000 |
		    SNDRV_PCM_RATE_88200 |
		    SNDRV_PCM_RATE_96000;
	snd_pcm_limit_hw_rates(runtime);

	return amdtp_tscm_add_pcm_hw_constraints(stream, runtime);
}