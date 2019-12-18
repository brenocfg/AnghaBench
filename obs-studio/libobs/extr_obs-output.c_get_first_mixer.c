#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t mixer_mask; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 size_t MAX_AUDIO_MIXES ; 

__attribute__((used)) static inline size_t get_first_mixer(const obs_output_t *output)
{
	for (size_t i = 0; i < MAX_AUDIO_MIXES; i++) {
		if ((((size_t)1 << i) & output->mixer_mask) != 0) {
			return i;
		}
	}

	return 0;
}