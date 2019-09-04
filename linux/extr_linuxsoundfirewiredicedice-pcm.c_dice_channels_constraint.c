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
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* pcm; struct snd_dice* private_data; } ;
struct snd_pcm_hw_rule {struct snd_pcm_substream* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {int integer; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct snd_dice {unsigned int** tx_pcm_chs; unsigned int** rx_pcm_chs; } ;
typedef  enum snd_dice_rate_mode { ____Placeholder_snd_dice_rate_mode } snd_dice_rate_mode ;
struct TYPE_2__ {unsigned int device; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  UINT_MAX ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_interval* hw_param_interval_c (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int* snd_dice_rates ; 
 scalar_t__ snd_dice_stream_get_rate_mode (struct snd_dice*,unsigned int,int*) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 
 int /*<<< orphan*/  snd_interval_test (struct snd_interval const*,unsigned int) ; 

__attribute__((used)) static int dice_channels_constraint(struct snd_pcm_hw_params *params,
				    struct snd_pcm_hw_rule *rule)
{
	struct snd_pcm_substream *substream = rule->private;
	struct snd_dice *dice = substream->private_data;
	unsigned int index = substream->pcm->device;

	const struct snd_interval *r =
		hw_param_interval_c(params, SNDRV_PCM_HW_PARAM_RATE);
	struct snd_interval *c =
		hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_interval channels = {
		.min = UINT_MAX, .max = 0, .integer = 1
	};
	unsigned int *pcm_channels;
	enum snd_dice_rate_mode mode;
	unsigned int i, rate;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		pcm_channels = dice->tx_pcm_chs[index];
	else
		pcm_channels = dice->rx_pcm_chs[index];

	for (i = 0; i < ARRAY_SIZE(snd_dice_rates); ++i) {
		rate = snd_dice_rates[i];
		if (snd_dice_stream_get_rate_mode(dice, rate, &mode) < 0)
			continue;

		if (!snd_interval_test(r, rate))
			continue;

		channels.min = min(channels.min, pcm_channels[mode]);
		channels.max = max(channels.max, pcm_channels[mode]);
	}

	return snd_interval_refine(c, &channels);
}