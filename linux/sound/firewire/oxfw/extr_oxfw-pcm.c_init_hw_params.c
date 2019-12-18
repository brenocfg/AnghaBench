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
typedef  int /*<<< orphan*/  u8 ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  formats; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct amdtp_stream {int dummy; } ;
struct snd_oxfw {int /*<<< orphan*/ ** rx_stream_formats; struct amdtp_stream rx_stream; int /*<<< orphan*/ ** tx_stream_formats; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM824_IN_PCM_FORMAT_BITS ; 
 int /*<<< orphan*/  AM824_OUT_PCM_FORMAT_BITS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int amdtp_am824_add_pcm_hw_constraints (struct amdtp_stream*,struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  hw_rule_channels ; 
 int /*<<< orphan*/  hw_rule_rate ; 
 int /*<<< orphan*/  limit_channels_and_rates (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_hw_params(struct snd_oxfw *oxfw,
			  struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	u8 **formats;
	struct amdtp_stream *stream;
	int err;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		runtime->hw.formats = AM824_IN_PCM_FORMAT_BITS;
		stream = &oxfw->tx_stream;
		formats = oxfw->tx_stream_formats;
	} else {
		runtime->hw.formats = AM824_OUT_PCM_FORMAT_BITS;
		stream = &oxfw->rx_stream;
		formats = oxfw->rx_stream_formats;
	}

	limit_channels_and_rates(&runtime->hw, formats);

	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  hw_rule_channels, formats,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		goto end;

	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				  hw_rule_rate, formats,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (err < 0)
		goto end;

	err = amdtp_am824_add_pcm_hw_constraints(stream, runtime);
end:
	return err;
}