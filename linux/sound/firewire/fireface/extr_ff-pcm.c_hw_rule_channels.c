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
struct snd_pcm_hw_rule {unsigned int* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {int integer; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  enum snd_ff_stream_mode { ____Placeholder_snd_ff_stream_mode } snd_ff_stream_mode ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/ * amdtp_rate_table ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_interval* hw_param_interval_c (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int const) ; 
 int snd_ff_stream_get_multiplier_mode (unsigned int,int*) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 
 int /*<<< orphan*/  snd_interval_test (struct snd_interval const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_rule_channels(struct snd_pcm_hw_params *params,
			    struct snd_pcm_hw_rule *rule)
{
	const unsigned int *pcm_channels = rule->private;
	struct snd_interval *c =
		hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	const struct snd_interval *r =
		hw_param_interval_c(params, SNDRV_PCM_HW_PARAM_RATE);
	struct snd_interval t = {
		.min = UINT_MAX, .max = 0, .integer = 1
	};
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(amdtp_rate_table); i++) {
		enum snd_ff_stream_mode mode;
		int err;

		err = snd_ff_stream_get_multiplier_mode(i, &mode);
		if (err < 0)
			continue;

		if (!snd_interval_test(r, amdtp_rate_table[i]))
			continue;

		t.min = min(t.min, pcm_channels[mode]);
		t.max = max(t.max, pcm_channels[mode]);
	}

	return snd_interval_refine(c, &t);
}