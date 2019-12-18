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
struct mem_cgroup {TYPE_1__* vmstats_percpu; } ;
typedef  enum mem_cgroup_events_target { ____Placeholder_mem_cgroup_events_target } mem_cgroup_events_target ;
struct TYPE_2__ {int /*<<< orphan*/ * targets; int /*<<< orphan*/  nr_page_events; } ;

/* Variables and functions */
#define  MEM_CGROUP_TARGET_NUMAINFO 130 
#define  MEM_CGROUP_TARGET_SOFTLIMIT 129 
#define  MEM_CGROUP_TARGET_THRESH 128 
 int /*<<< orphan*/  NUMAINFO_EVENTS_TARGET ; 
 int /*<<< orphan*/  SOFTLIMIT_EVENTS_TARGET ; 
 int /*<<< orphan*/  THRESHOLDS_EVENTS_TARGET ; 
 unsigned long __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bool mem_cgroup_event_ratelimit(struct mem_cgroup *memcg,
				       enum mem_cgroup_events_target target)
{
	unsigned long val, next;

	val = __this_cpu_read(memcg->vmstats_percpu->nr_page_events);
	next = __this_cpu_read(memcg->vmstats_percpu->targets[target]);
	/* from time_after() in jiffies.h */
	if ((long)(next - val) < 0) {
		switch (target) {
		case MEM_CGROUP_TARGET_THRESH:
			next = val + THRESHOLDS_EVENTS_TARGET;
			break;
		case MEM_CGROUP_TARGET_SOFTLIMIT:
			next = val + SOFTLIMIT_EVENTS_TARGET;
			break;
		case MEM_CGROUP_TARGET_NUMAINFO:
			next = val + NUMAINFO_EVENTS_TARGET;
			break;
		default:
			break;
		}
		__this_cpu_write(memcg->vmstats_percpu->targets[target], next);
		return true;
	}
	return false;
}