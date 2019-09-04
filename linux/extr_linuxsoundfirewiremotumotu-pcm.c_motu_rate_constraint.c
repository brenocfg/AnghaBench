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
struct snd_pcm_hw_rule {struct snd_motu_packet_format* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_motu_packet_format {unsigned int* fixed_part_pcm_chunks; unsigned int* differed_part_pcm_chunks; } ;
struct snd_interval {int integer; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  UINT_MAX ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_interval* hw_param_interval_c (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 
 int /*<<< orphan*/  snd_interval_test (struct snd_interval const*,unsigned int) ; 
 unsigned int* snd_motu_clock_rates ; 

__attribute__((used)) static int motu_rate_constraint(struct snd_pcm_hw_params *params,
				struct snd_pcm_hw_rule *rule)
{
	struct snd_motu_packet_format *formats = rule->private;

	const struct snd_interval *c =
		hw_param_interval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_interval *r =
		hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);
	struct snd_interval rates = {
		.min = UINT_MAX, .max = 0, .integer = 1
	};
	unsigned int i, pcm_channels, rate, mode;

	for (i = 0; i < ARRAY_SIZE(snd_motu_clock_rates); ++i) {
		rate = snd_motu_clock_rates[i];
		mode = i / 2;

		pcm_channels = formats->fixed_part_pcm_chunks[mode] +
			       formats->differed_part_pcm_chunks[mode];
		if (!snd_interval_test(c, pcm_channels))
			continue;

		rates.min = min(rates.min, rate);
		rates.max = max(rates.max, rate);
	}

	return snd_interval_refine(r, &rates);
}