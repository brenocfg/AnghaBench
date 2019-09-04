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
struct hw_perf_event {int idx; } ;
struct perf_event {int /*<<< orphan*/  cpu; int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;
struct cluster_pmu {int /*<<< orphan*/ ** events; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 struct cluster_pmu* get_cluster_pmu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2_cache_clear_event_idx (struct cluster_pmu*,struct perf_event*) ; 
 int /*<<< orphan*/  l2_cache_event_stop (struct perf_event*,int) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  to_l2cache_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2_cache_event_del(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	struct cluster_pmu *cluster;
	int idx = hwc->idx;

	cluster = get_cluster_pmu(to_l2cache_pmu(event->pmu), event->cpu);

	l2_cache_event_stop(event, flags | PERF_EF_UPDATE);
	cluster->events[idx] = NULL;
	l2_cache_clear_event_idx(cluster, event);

	perf_event_update_userpage(event);
}