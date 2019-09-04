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
struct snd_pcm_hardware {scalar_t__ channels_max; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {struct snd_pcm_hardware hw; } ;
struct snd_motu_packet_format {unsigned int* fixed_part_pcm_chunks; unsigned int* differed_part_pcm_chunks; } ;
struct snd_motu {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 scalar_t__ max (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int* snd_motu_clock_rates ; 
 int /*<<< orphan*/  snd_pcm_limit_hw_rates (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_pcm_rate_to_rate_bit (unsigned int) ; 

__attribute__((used)) static void limit_channels_and_rates(struct snd_motu *motu,
				     struct snd_pcm_runtime *runtime,
				     struct snd_motu_packet_format *formats)
{
	struct snd_pcm_hardware *hw = &runtime->hw;
	unsigned int i, pcm_channels, rate, mode;

	hw->channels_min = UINT_MAX;
	hw->channels_max = 0;

	for (i = 0; i < ARRAY_SIZE(snd_motu_clock_rates); ++i) {
		rate = snd_motu_clock_rates[i];
		mode = i / 2;

		pcm_channels = formats->fixed_part_pcm_chunks[mode] +
			       formats->differed_part_pcm_chunks[mode];
		if (pcm_channels == 0)
			continue;

		hw->rates |= snd_pcm_rate_to_rate_bit(rate);
		hw->channels_min = min(hw->channels_min, pcm_channels);
		hw->channels_max = max(hw->channels_max, pcm_channels);
	}

	snd_pcm_limit_hw_rates(runtime);
}