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
struct perf_thread_map {int dummy; } ;
struct TYPE_2__ {struct perf_thread_map* color_pids; int /*<<< orphan*/  color_pids_str; } ;
struct perf_sched {TYPE_1__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 struct perf_thread_map* thread_map__new_by_tid_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_color_pids(struct perf_sched *sched)
{
	struct perf_thread_map *map;

	if (!sched->map.color_pids_str)
		return 0;

	map = thread_map__new_by_tid_str(sched->map.color_pids_str);
	if (!map) {
		pr_err("failed to get thread map from %s\n", sched->map.color_pids_str);
		return -1;
	}

	sched->map.color_pids = map;
	return 0;
}