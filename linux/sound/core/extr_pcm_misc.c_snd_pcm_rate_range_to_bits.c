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
struct TYPE_2__ {int count; unsigned int* list; } ;

/* Variables and functions */
 unsigned int SNDRV_PCM_RATE_KNOT ; 
 TYPE_1__ snd_pcm_known_rates ; 

unsigned int snd_pcm_rate_range_to_bits(unsigned int rate_min,
	unsigned int rate_max)
{
	unsigned int rates = 0;
	int i;

	for (i = 0; i < snd_pcm_known_rates.count; i++) {
		if (snd_pcm_known_rates.list[i] >= rate_min
			&& snd_pcm_known_rates.list[i] <= rate_max)
			rates |= 1 << i;
	}

	if (!rates)
		rates = SNDRV_PCM_RATE_KNOT;

	return rates;
}