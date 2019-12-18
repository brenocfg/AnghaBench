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
struct perf_stat {int maps_allocated; int /*<<< orphan*/  threads; int /*<<< orphan*/  cpus; } ;
struct TYPE_3__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 TYPE_1__* evsel_list ; 
 scalar_t__ perf_evlist__alloc_stats (TYPE_1__*,int) ; 
 int /*<<< orphan*/  perf_evlist__set_maps (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_maps(struct perf_stat *st)
{
	if (!st->cpus || !st->threads)
		return 0;

	if (WARN_ONCE(st->maps_allocated, "stats double allocation\n"))
		return -EINVAL;

	perf_evlist__set_maps(&evsel_list->core, st->cpus, st->threads);

	if (perf_evlist__alloc_stats(evsel_list, true))
		return -ENOMEM;

	st->maps_allocated = true;
	return 0;
}