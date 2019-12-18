#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {scalar_t__ time_delta; scalar_t__ count; } ;
typedef  TYPE_2__ profiler_time_entry ;
typedef  int /*<<< orphan*/  profiler_time_entries_t ;
struct TYPE_9__ {size_t size; TYPE_1__* entries; int /*<<< orphan*/  occupied; } ;
typedef  TYPE_3__ profile_times_table ;
struct TYPE_7__ {TYPE_2__ entry; int /*<<< orphan*/  probes; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  da_reserve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  migrate_old_entries (TYPE_3__*,int) ; 

__attribute__((used)) static uint64_t copy_map_to_array(profile_times_table *map,
				  profiler_time_entries_t *entry_buffer,
				  uint64_t *min_, uint64_t *max_)
{
	migrate_old_entries(map, false);

	da_reserve((*entry_buffer), map->occupied);
	da_resize((*entry_buffer), 0);

	uint64_t min__ = ~(uint64_t)0;
	uint64_t max__ = 0;

	uint64_t calls = 0;
	for (size_t i = 0; i < map->size; i++) {
		if (!map->entries[i].probes)
			continue;

		profiler_time_entry *entry = &map->entries[i].entry;

		da_push_back((*entry_buffer), entry);

		calls += entry->count;
		min__ = (min__ < entry->time_delta) ? min__ : entry->time_delta;
		max__ = (max__ > entry->time_delta) ? max__ : entry->time_delta;
	}

	if (min_)
		*min_ = min__;
	if (max_)
		*max_ = max__;

	return calls;
}