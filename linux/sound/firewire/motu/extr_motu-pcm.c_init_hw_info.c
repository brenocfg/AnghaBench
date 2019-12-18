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
struct snd_pcm_hardware {void* formats; } ;
struct snd_pcm_runtime {struct snd_pcm_hardware hw; } ;
struct snd_motu_packet_format {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct snd_motu {struct snd_motu_packet_format rx_packet_formats; struct amdtp_stream rx_stream; struct snd_motu_packet_format tx_packet_formats; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 void* SNDRV_PCM_FMTBIT_S32 ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int amdtp_motu_add_pcm_hw_constraints (struct amdtp_stream*,struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  limit_channels_and_rates (struct snd_motu*,struct snd_pcm_runtime*,struct snd_motu_packet_format*) ; 
 int /*<<< orphan*/  motu_channels_constraint ; 
 int /*<<< orphan*/  motu_rate_constraint ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_motu_packet_format*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_hw_info(struct snd_motu *motu,
			struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_pcm_hardware *hw = &runtime->hw;
	struct amdtp_stream *stream;
	struct snd_motu_packet_format *formats;
	int err;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		hw->formats = SNDRV_PCM_FMTBIT_S32;
		stream = &motu->tx_stream;
		formats = &motu->tx_packet_formats;
	} else {
		hw->formats = SNDRV_PCM_FMTBIT_S32;
		stream = &motu->rx_stream;
		formats = &motu->rx_packet_formats;
	}

	limit_channels_and_rates(motu, runtime, formats);

	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				  motu_rate_constraint, formats,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  motu_channels_constraint, formats,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		return err;

	return amdtp_motu_add_pcm_hw_constraints(stream, runtime);
}