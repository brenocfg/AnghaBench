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
struct TYPE_3__ {size_t max_probe_count; } ;
typedef  TYPE_1__ profile_times_table ;

/* Variables and functions */

__attribute__((used)) static inline void update_max_probes(profile_times_table *map, size_t val)
{
	map->max_probe_count = map->max_probe_count < val ?
		val : map->max_probe_count;
}