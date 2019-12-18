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
struct TYPE_7__ {int /*<<< orphan*/  count; int /*<<< orphan*/  time_delta; } ;
struct TYPE_8__ {TYPE_1__ entry; int /*<<< orphan*/  probes; } ;
typedef  TYPE_2__ profile_times_table_entry ;
struct TYPE_9__ {size_t old_start_index; scalar_t__ old_occupied; TYPE_2__* old_entries; } ;
typedef  TYPE_3__ profile_times_table ;

/* Variables and functions */
 int /*<<< orphan*/  add_hashmap_entry (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (TYPE_2__*) ; 

__attribute__((used)) static void migrate_old_entries(profile_times_table *map, bool limit_items)
{
	if (!map->old_entries)
		return;

	if (!map->old_occupied) {
		bfree(map->old_entries);
		map->old_entries = NULL;
		return;
	}

	for (size_t i = 0; !limit_items || i < 8; i++, map->old_start_index++) {
		if (!map->old_occupied)
			return;

		profile_times_table_entry *entry =
			&map->old_entries[map->old_start_index];
		if (!entry->probes)
			continue;

		add_hashmap_entry(map, entry->entry.time_delta,
				  entry->entry.count);
		map->old_occupied -= 1;
	}
}