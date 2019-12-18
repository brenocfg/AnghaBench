#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  prev; int /*<<< orphan*/  overwrite; } ;
struct mmap {TYPE_1__ core; } ;

/* Variables and functions */
 scalar_t__ perf_mmap__empty (struct mmap*) ; 
 int /*<<< orphan*/  perf_mmap__put (struct mmap*) ; 
 int /*<<< orphan*/  perf_mmap__write_tail (struct mmap*,int /*<<< orphan*/ ) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

void perf_mmap__consume(struct mmap *map)
{
	if (!map->core.overwrite) {
		u64 old = map->core.prev;

		perf_mmap__write_tail(map, old);
	}

	if (refcount_read(&map->core.refcnt) == 1 && perf_mmap__empty(map))
		perf_mmap__put(map);
}