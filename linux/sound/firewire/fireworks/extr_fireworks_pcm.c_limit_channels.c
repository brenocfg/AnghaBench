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
struct snd_pcm_hardware {int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  freq_table ; 
 unsigned int get_multiplier_mode_with_index (unsigned int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
limit_channels(struct snd_pcm_hardware *hw, unsigned int *pcm_channels)
{
	unsigned int i, mode;

	hw->channels_min = UINT_MAX;
	hw->channels_max = 0;

	for (i = 0; i < ARRAY_SIZE(freq_table); i++) {
		mode = get_multiplier_mode_with_index(i);
		if (pcm_channels[mode] == 0)
			continue;

		hw->channels_min = min(hw->channels_min, pcm_channels[mode]);
		hw->channels_max = max(hw->channels_max, pcm_channels[mode]);
	}
}