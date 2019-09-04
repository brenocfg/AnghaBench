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
struct TYPE_4__ {double count; double time_delta; } ;
typedef  TYPE_1__ profiler_time_entry ;
struct TYPE_5__ {size_t num; TYPE_1__* array; } ;
typedef  TYPE_2__ profiler_time_entries_t ;

/* Variables and functions */

__attribute__((used)) static void gather_stats(uint64_t expected_time_between_calls,
		profiler_time_entries_t *entries,
		uint64_t calls, uint64_t *percentile99, uint64_t *median,
		double *percent_within_bounds)
{
	if (!entries->num) {
		*percentile99 = 0;
		*median = 0;
		*percent_within_bounds = 0.;
		return;
	}

	/*if (entry_buffer->num > 2)
		blog(LOG_INFO, "buffer-size %lu, overall count %llu\n"
				"map-size %lu, occupied %lu, probes %lu",
				entry_buffer->num, calls,
				map->size, map->occupied,
				map->max_probe_count);*/
	uint64_t accu = 0;
	for (size_t i = 0; i < entries->num; i++) {
		uint64_t old_accu = accu;
		accu += entries->array[i].count;

		if (old_accu < calls * 0.01 && accu >= calls * 0.01)
			*percentile99 = entries->array[i].time_delta;
		else if (old_accu < calls * 0.5 && accu >= calls * 0.5) {
			*median = entries->array[i].time_delta;
			break;
		}
	}

	*percent_within_bounds = 0.;
	if (!expected_time_between_calls)
		return;

	accu = 0;
	for (size_t i = 0; i < entries->num; i++) {
		profiler_time_entry *entry = &entries->array[i];
		if (entry->time_delta < expected_time_between_calls)
			break;

		accu += entry->count;
	}
	*percent_within_bounds = (1. - (double)accu / calls) * 100;
}