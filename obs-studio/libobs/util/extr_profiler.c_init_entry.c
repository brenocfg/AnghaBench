#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* name; int /*<<< orphan*/  times_between_calls; scalar_t__ expected_time_between_calls; int /*<<< orphan*/  overhead; int /*<<< orphan*/  times; } ;
typedef  TYPE_1__ profile_entry ;

/* Variables and functions */
 int /*<<< orphan*/  init_hashmap (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static profile_entry *init_entry(profile_entry *entry, const char *name)
{
	entry->name = name;
	init_hashmap(&entry->times, 1);
#ifdef TRACK_OVERHEAD
	init_hashmap(&entry->overhead, 1);
#endif
	entry->expected_time_between_calls = 0;
	init_hashmap(&entry->times_between_calls, 1);
	return entry;
}