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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_hardware {int channels_min; int channels_max; int rates; void* formats; } ;
struct snd_pcm_runtime {struct snd_pcm_hardware hw; } ;
struct amdtp_stream {int dummy; } ;
struct snd_dg00x {struct amdtp_stream rx_stream; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 void* SNDRV_PCM_FMTBIT_S32 ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int SNDRV_PCM_RATE_44100 ; 
 int SNDRV_PCM_RATE_48000 ; 
 int SNDRV_PCM_RATE_88200 ; 
 int SNDRV_PCM_RATE_96000 ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int amdtp_dot_add_pcm_hw_constraints (struct amdtp_stream*,struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  hw_rule_channels ; 
 int /*<<< orphan*/  hw_rule_rate ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_limit_hw_rates (struct snd_pcm_runtime*) ; 

__attribute__((used)) static int pcm_init_hw_params(struct snd_dg00x *dg00x,
			      struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_pcm_hardware *hw = &runtime->hw;
	struct amdtp_stream *s;
	int err;


	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		substream->runtime->hw.formats = SNDRV_PCM_FMTBIT_S32;
		s = &dg00x->tx_stream;
	} else {
		substream->runtime->hw.formats = SNDRV_PCM_FMTBIT_S32;
		s = &dg00x->rx_stream;
	}

	hw->channels_min = 10;
	hw->channels_max = 18;

	hw->rates = SNDRV_PCM_RATE_44100 |
		    SNDRV_PCM_RATE_48000 |
		    SNDRV_PCM_RATE_88200 |
		    SNDRV_PCM_RATE_96000;
	snd_pcm_limit_hw_rates(runtime);

	err = snd_pcm_hw_rule_add(substream->runtime, 0,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  hw_rule_channels, NULL,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		return err;

	err = snd_pcm_hw_rule_add(substream->runtime, 0,
				  SNDRV_PCM_HW_PARAM_RATE,
				  hw_rule_rate, NULL,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (err < 0)
		return err;

	return amdtp_dot_add_pcm_hw_constraints(s, substream->runtime);
}