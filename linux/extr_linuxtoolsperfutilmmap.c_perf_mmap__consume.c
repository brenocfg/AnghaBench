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
typedef  int /*<<< orphan*/  u64 ;
struct perf_mmap {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  prev; int /*<<< orphan*/  overwrite; } ;

/* Variables and functions */
 scalar_t__ perf_mmap__empty (struct perf_mmap*) ; 
 int /*<<< orphan*/  perf_mmap__put (struct perf_mmap*) ; 
 int /*<<< orphan*/  perf_mmap__write_tail (struct perf_mmap*,int /*<<< orphan*/ ) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

void perf_mmap__consume(struct perf_mmap *map)
{
	if (!map->overwrite) {
		u64 old = map->prev;

		perf_mmap__write_tail(map, old);
	}

	if (refcount_read(&map->refcnt) == 1 && perf_mmap__empty(map))
		perf_mmap__put(map);
}