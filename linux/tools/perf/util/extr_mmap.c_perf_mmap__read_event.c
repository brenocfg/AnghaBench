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
typedef  union perf_event {int dummy; } perf_event ;
struct TYPE_2__ {int /*<<< orphan*/  start; int /*<<< orphan*/  prev; int /*<<< orphan*/  overwrite; int /*<<< orphan*/  end; int /*<<< orphan*/  refcnt; } ;
struct mmap {TYPE_1__ core; } ;

/* Variables and functions */
 union perf_event* perf_mmap__read (struct mmap*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_mmap__read_head (struct mmap*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

union perf_event *perf_mmap__read_event(struct mmap *map)
{
	union perf_event *event;

	/*
	 * Check if event was unmapped due to a POLLHUP/POLLERR.
	 */
	if (!refcount_read(&map->core.refcnt))
		return NULL;

	/* non-overwirte doesn't pause the ringbuffer */
	if (!map->core.overwrite)
		map->core.end = perf_mmap__read_head(map);

	event = perf_mmap__read(map, &map->core.start, map->core.end);

	if (!map->core.overwrite)
		map->core.prev = map->core.start;

	return event;
}