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
struct snd_pcm_chmap {int max_channels; unsigned int channel_mask; } ;

/* Variables and functions */

__attribute__((used)) static bool valid_chmap_channels(const struct snd_pcm_chmap *info, int ch)
{
	if (ch > info->max_channels)
		return false;
	return !info->channel_mask || (info->channel_mask & (1U << ch));
}