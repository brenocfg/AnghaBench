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
struct snd_pcm_hardware {void* rate_max; void* rate_min; int /*<<< orphan*/  rates; void* channels_max; void* channels_min; } ;
typedef  enum snd_ff_stream_mode { ____Placeholder_snd_ff_stream_mode } snd_ff_stream_mode ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 void* UINT_MAX ; 
 unsigned int* amdtp_rate_table ; 
 void* max (void*,unsigned int) ; 
 void* min (void*,unsigned int) ; 
 int snd_ff_stream_get_multiplier_mode (int,int*) ; 
 int /*<<< orphan*/  snd_pcm_rate_to_rate_bit (unsigned int) ; 

__attribute__((used)) static void limit_channels_and_rates(struct snd_pcm_hardware *hw,
				     const unsigned int *pcm_channels)
{
	unsigned int rate, channels;
	int i;

	hw->channels_min = UINT_MAX;
	hw->channels_max = 0;
	hw->rate_min = UINT_MAX;
	hw->rate_max = 0;

	for (i = 0; i < ARRAY_SIZE(amdtp_rate_table); i++) {
		enum snd_ff_stream_mode mode;
		int err;

		err = snd_ff_stream_get_multiplier_mode(i, &mode);
		if (err < 0)
			continue;

		channels = pcm_channels[mode];
		if (pcm_channels[mode] == 0)
			continue;
		hw->channels_min = min(hw->channels_min, channels);
		hw->channels_max = max(hw->channels_max, channels);

		rate = amdtp_rate_table[i];
		hw->rates |= snd_pcm_rate_to_rate_bit(rate);
		hw->rate_min = min(hw->rate_min, rate);
		hw->rate_max = max(hw->rate_max, rate);
	}
}