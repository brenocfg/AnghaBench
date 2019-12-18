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
struct TYPE_3__ {int /*<<< orphan*/ * old_entries; int /*<<< orphan*/ * entries; scalar_t__ size; } ;
typedef  TYPE_1__ profile_times_table ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_hashmap(profile_times_table *map)
{
	map->size = 0;
	bfree(map->entries);
	map->entries = NULL;
	bfree(map->old_entries);
	map->old_entries = NULL;
}