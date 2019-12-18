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
 int MAX_AUDIO_MIXES ; 

__attribute__((used)) static int get_audio_mix_count(int audio_mix_mask)
{
	int mix_count = 0;
	for (int i = 0; i < MAX_AUDIO_MIXES; i++) {
		if ((audio_mix_mask & (1 << i)) != 0) {
			mix_count++;
		}
	}

	return mix_count;
}