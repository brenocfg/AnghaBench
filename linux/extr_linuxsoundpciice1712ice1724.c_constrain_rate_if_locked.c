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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {unsigned int rate_min; unsigned int rate_max; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct snd_ice1712 {unsigned int (* get_rate ) (struct snd_ice1712*) ;} ;

/* Variables and functions */
 scalar_t__ is_pro_rate_locked (struct snd_ice1712*) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 unsigned int stub1 (struct snd_ice1712*) ; 

__attribute__((used)) static void constrain_rate_if_locked(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int rate;
	if (is_pro_rate_locked(ice)) {
		rate = ice->get_rate(ice);
		if (rate >= runtime->hw.rate_min
		    && rate <= runtime->hw.rate_max) {
			runtime->hw.rate_min = rate;
			runtime->hw.rate_max = rate;
		}
	}
}