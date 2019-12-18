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
struct pmu_event_list {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct perf_event {int /*<<< orphan*/  sb_list; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pmu_event_list* per_cpu_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_sb_events ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void attach_sb_event(struct perf_event *event)
{
	struct pmu_event_list *pel = per_cpu_ptr(&pmu_sb_events, event->cpu);

	raw_spin_lock(&pel->lock);
	list_add_rcu(&event->sb_list, &pel->list);
	raw_spin_unlock(&pel->lock);
}