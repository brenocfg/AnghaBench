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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  formats; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct snd_bebob_stream_formation {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct snd_bebob {struct snd_bebob_stream_formation* rx_stream_formations; struct amdtp_stream rx_stream; struct snd_bebob_stream_formation* tx_stream_formations; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM824_IN_PCM_FORMAT_BITS ; 
 int /*<<< orphan*/  AM824_OUT_PCM_FORMAT_BITS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int amdtp_am824_add_pcm_hw_constraints (struct amdtp_stream*,struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  hw_rule_channels ; 
 int /*<<< orphan*/  hw_rule_rate ; 
 int /*<<< orphan*/  limit_channels_and_rates (TYPE_1__*,struct snd_bebob_stream_formation*) ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_bebob_stream_formation*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pcm_init_hw_params(struct snd_bebob *bebob,
		   struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct amdtp_stream *s;
	struct snd_bebob_stream_formation *formations;
	int err;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		runtime->hw.formats = AM824_IN_PCM_FORMAT_BITS;
		s = &bebob->tx_stream;
		formations = bebob->tx_stream_formations;
	} else {
		runtime->hw.formats = AM824_OUT_PCM_FORMAT_BITS;
		s = &bebob->rx_stream;
		formations = bebob->rx_stream_formations;
	}

	limit_channels_and_rates(&runtime->hw, formations);

	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  hw_rule_channels, formations,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		goto end;

	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				  hw_rule_rate, formations,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (err < 0)
		goto end;

	err = amdtp_am824_add_pcm_hw_constraints(s, runtime);
end:
	return err;
}