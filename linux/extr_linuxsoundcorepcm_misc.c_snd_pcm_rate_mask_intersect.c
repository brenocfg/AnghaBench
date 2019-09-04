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

/* Variables and functions */
 unsigned int SNDRV_PCM_RATE_CONTINUOUS ; 
 unsigned int SNDRV_PCM_RATE_KNOT ; 
 unsigned int snd_pcm_rate_mask_sanitize (unsigned int) ; 

unsigned int snd_pcm_rate_mask_intersect(unsigned int rates_a,
	unsigned int rates_b)
{
	rates_a = snd_pcm_rate_mask_sanitize(rates_a);
	rates_b = snd_pcm_rate_mask_sanitize(rates_b);

	if (rates_a & SNDRV_PCM_RATE_CONTINUOUS)
		return rates_b;
	else if (rates_b & SNDRV_PCM_RATE_CONTINUOUS)
		return rates_a;
	else if (rates_a & SNDRV_PCM_RATE_KNOT)
		return rates_b;
	else if (rates_b & SNDRV_PCM_RATE_KNOT)
		return rates_a;
	return rates_a & rates_b;
}