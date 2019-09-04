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
struct TYPE_2__ {unsigned int count; unsigned int* list; } ;

/* Variables and functions */
 TYPE_1__ snd_pcm_known_rates ; 

unsigned int snd_pcm_rate_bit_to_rate(unsigned int rate_bit)
{
	unsigned int i;

	for (i = 0; i < snd_pcm_known_rates.count; i++)
		if ((1u << i) == rate_bit)
			return snd_pcm_known_rates.list[i];
	return 0;
}