#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  profile_times_table_entry ;
struct TYPE_6__ {size_t size; size_t occupied; size_t old_occupied; int /*<<< orphan*/ * old_entries; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ profile_times_table ;

/* Variables and functions */
 int /*<<< orphan*/  add_hashmap_entry (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_hashmap (TYPE_1__*,int) ; 
 int /*<<< orphan*/  migrate_old_entries (TYPE_1__*,int) ; 

__attribute__((used)) static void grow_hashmap(profile_times_table *map, uint64_t usec,
			 uint64_t count)
{
	migrate_old_entries(map, false);

	size_t old_size = map->size;
	size_t old_occupied = map->occupied;
	profile_times_table_entry *entries = map->entries;

	init_hashmap(map, (old_size * 2 < 16) ? 16 : (old_size * 2));

	map->old_occupied = old_occupied;
	map->old_entries = entries;

	add_hashmap_entry(map, usec, count);
}