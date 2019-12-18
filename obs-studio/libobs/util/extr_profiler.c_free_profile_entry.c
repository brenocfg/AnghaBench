#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num; TYPE_1__* array; } ;
struct TYPE_4__ {TYPE_3__ children; int /*<<< orphan*/  times_between_calls; int /*<<< orphan*/  overhead; int /*<<< orphan*/  times; } ;
typedef  TYPE_1__ profile_entry ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_3__) ; 
 int /*<<< orphan*/  free_hashmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_profile_entry(profile_entry *entry)
{
	for (size_t i = 0; i < entry->children.num; i++)
		free_profile_entry(&entry->children.array[i]);

	free_hashmap(&entry->times);
#ifdef TRACK_OVERHEAD
	free_hashmap(&entry->overhead);
#endif
	free_hashmap(&entry->times_between_calls);
	da_free(entry->children);
}