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
typedef  int /*<<< orphan*/  uint64_t ;
struct obs_core_data {int dummy; } ;

/* Variables and functions */
 char* find_min_ts (struct obs_core_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ mark_invalid_sources (struct obs_core_data*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *calc_min_ts(struct obs_core_data *data,
				      size_t sample_rate, uint64_t *min_ts)
{
	const char *buffering_name = find_min_ts(data, min_ts);
	if (mark_invalid_sources(data, sample_rate, *min_ts))
		buffering_name = find_min_ts(data, min_ts);
	return buffering_name;
}