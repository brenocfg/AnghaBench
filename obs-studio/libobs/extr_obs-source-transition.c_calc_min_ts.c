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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ audio_ts; int /*<<< orphan*/  audio_pending; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t calc_min_ts(obs_source_t *sources[2])
{
	uint64_t min_ts = 0;

	for (size_t i = 0; i < 2; i++) {
		if (sources[i] && !sources[i]->audio_pending) {
			if (!min_ts || sources[i]->audio_ts < min_ts)
				min_ts = sources[i]->audio_ts;
		}
	}

	return min_ts;
}