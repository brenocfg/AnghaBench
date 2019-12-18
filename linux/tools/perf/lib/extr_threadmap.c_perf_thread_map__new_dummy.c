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
struct perf_thread_map {int nr; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_thread_map__set_pid (struct perf_thread_map*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 struct perf_thread_map* thread_map__alloc (int) ; 

struct perf_thread_map *perf_thread_map__new_dummy(void)
{
	struct perf_thread_map *threads = thread_map__alloc(1);

	if (threads != NULL) {
		perf_thread_map__set_pid(threads, 0, -1);
		threads->nr = 1;
		refcount_set(&threads->refcnt, 1);
	}
	return threads;
}