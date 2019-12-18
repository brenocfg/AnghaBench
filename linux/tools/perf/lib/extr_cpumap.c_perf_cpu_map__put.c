#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct perf_cpu_map {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_map__delete (struct perf_cpu_map*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void perf_cpu_map__put(struct perf_cpu_map *map)
{
	if (map && refcount_dec_and_test(&map->refcnt))
		cpu_map__delete(map);
}