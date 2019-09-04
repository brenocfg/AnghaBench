#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rates; int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/ * list; scalar_t__ count; } ;

/* Variables and functions */
 TYPE_2__ snd_pcm_known_rates ; 

int snd_pcm_limit_hw_rates(struct snd_pcm_runtime *runtime)
{
	int i;
	for (i = 0; i < (int)snd_pcm_known_rates.count; i++) {
		if (runtime->hw.rates & (1 << i)) {
			runtime->hw.rate_min = snd_pcm_known_rates.list[i];
			break;
		}
	}
	for (i = (int)snd_pcm_known_rates.count - 1; i >= 0; i--) {
		if (runtime->hw.rates & (1 << i)) {
			runtime->hw.rate_max = snd_pcm_known_rates.list[i];
			break;
		}
	}
	return 0;
}