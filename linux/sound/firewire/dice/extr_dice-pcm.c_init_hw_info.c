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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; TYPE_1__* pcm; } ;
struct snd_pcm_hardware {int /*<<< orphan*/  formats; } ;
struct snd_pcm_runtime {struct snd_pcm_hardware hw; } ;
struct snd_dice {struct amdtp_stream* rx_stream; struct amdtp_stream* tx_stream; } ;
struct amdtp_stream {int dummy; } ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;
struct TYPE_2__ {unsigned int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM824_IN_PCM_FORMAT_BITS ; 
 int /*<<< orphan*/  AM824_OUT_PCM_FORMAT_BITS ; 
 int AMDTP_IN_STREAM ; 
 int AMDTP_OUT_STREAM ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int amdtp_am824_add_pcm_hw_constraints (struct amdtp_stream*,struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  dice_channels_constraint ; 
 int /*<<< orphan*/  dice_rate_constraint ; 
 int limit_channels_and_rates (struct snd_dice*,struct snd_pcm_runtime*,int,unsigned int) ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm_substream*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_hw_info(struct snd_dice *dice,
			struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_pcm_hardware *hw = &runtime->hw;
	unsigned int index = substream->pcm->device;
	enum amdtp_stream_direction dir;
	struct amdtp_stream *stream;
	int err;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		hw->formats = AM824_IN_PCM_FORMAT_BITS;
		dir = AMDTP_IN_STREAM;
		stream = &dice->tx_stream[index];
	} else {
		hw->formats = AM824_OUT_PCM_FORMAT_BITS;
		dir = AMDTP_OUT_STREAM;
		stream = &dice->rx_stream[index];
	}

	err = limit_channels_and_rates(dice, substream->runtime, dir,
				       index);
	if (err < 0)
		return err;

	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				  dice_rate_constraint, substream,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  dice_channels_constraint, substream,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		return err;

	return amdtp_am824_add_pcm_hw_constraints(stream, runtime);
}