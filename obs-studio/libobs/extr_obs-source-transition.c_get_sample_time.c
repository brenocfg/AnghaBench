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
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 float calc_time (int /*<<< orphan*/ *,unsigned long long) ; 

__attribute__((used)) static inline float get_sample_time(obs_source_t *transition,
				    size_t sample_rate, size_t sample,
				    uint64_t ts)
{
	uint64_t sample_ts_offset =
		(uint64_t)sample * 1000000000ULL / (uint64_t)sample_rate;
	uint64_t i_ts = ts + sample_ts_offset;
	return calc_time(transition, i_ts);
}