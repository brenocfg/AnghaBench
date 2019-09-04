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
typedef  int /*<<< orphan*/  profile_times_table_entry ;
struct TYPE_3__ {size_t size; int /*<<< orphan*/ * old_entries; scalar_t__ old_occupied; scalar_t__ old_start_index; int /*<<< orphan*/  entries; scalar_t__ max_probe_count; scalar_t__ occupied; } ;
typedef  TYPE_1__ profile_times_table ;

/* Variables and functions */
 int /*<<< orphan*/  bzalloc (int) ; 

__attribute__((used)) static void init_hashmap(profile_times_table *map, size_t size)
{
	map->size = size;
	map->occupied = 0;
	map->max_probe_count = 0;
	map->entries = bzalloc(sizeof(profile_times_table_entry) * size);
	map->old_start_index = 0;
	map->old_occupied = 0;
	map->old_entries = NULL;
}