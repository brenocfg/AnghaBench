#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  double uint64_t ;
struct TYPE_5__ {size_t num; TYPE_1__* array; } ;
typedef  TYPE_2__ profiler_time_entries_t ;
struct TYPE_4__ {double time_delta; scalar_t__ count; } ;

/* Variables and functions */

__attribute__((used)) static void gather_stats_between(profiler_time_entries_t *entries,
		uint64_t calls, uint64_t lower_bound, uint64_t upper_bound,
		uint64_t min_, uint64_t max_, uint64_t *median,
		double *percent, double *lower, double *higher)
{
	*median = 0;
	*percent = 0.;
	*lower = 0.;
	*higher = 0.;

	if (!entries->num)
		return;

	uint64_t accu = 0;
	for (size_t i = 0; i < entries->num; i++) {
		accu += entries->array[i].count;
		if (accu < calls * 0.5)
			continue;

		*median = entries->array[i].time_delta;
		break;
	}

	bool found_upper_bound = max_ <= upper_bound;
	bool found_lower_bound = false;

	if (min_ >= upper_bound) {
		*higher = 100.;
		return;
	}

	if (found_upper_bound && min_ >= lower_bound) {
		*percent = 100.;
		return;
	}

	accu = 0;
	for (size_t i = 0; i < entries->num; i++) {
		uint64_t delta = entries->array[i].time_delta;

		if (!found_upper_bound && delta <= upper_bound) {
			*higher = (double)accu / calls * 100;
			accu = 0;
			found_upper_bound = true;
		}

		if (!found_lower_bound && delta < lower_bound) {
			*percent = (double)accu / calls * 100;
			accu = 0;
			found_lower_bound = true;
		}

		accu += entries->array[i].count;
	}

	if (!found_upper_bound) {
		*higher = 100.;

	} else if (!found_lower_bound) {
		*percent = (double)accu / calls * 100;

	} else {
		*lower = (double)accu / calls * 100;
	}
}