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
struct TYPE_2__ {scalar_t__ bpf_event; scalar_t__ ksymbol; scalar_t__ context_switch; scalar_t__ freq; scalar_t__ task; scalar_t__ namespaces; scalar_t__ comm; scalar_t__ mmap_data; scalar_t__ mmap; } ;
struct perf_event {int attach_state; int /*<<< orphan*/  cpu; TYPE_1__ attr; scalar_t__ parent; } ;

/* Variables and functions */
 int PERF_ATTACH_TASK ; 
 int /*<<< orphan*/  account_event_cpu (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  account_freq_event () ; 
 int /*<<< orphan*/  account_pmu_sb_event (struct perf_event*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 scalar_t__ is_cgroup_event (struct perf_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_bpf_events ; 
 int /*<<< orphan*/  nr_comm_events ; 
 int /*<<< orphan*/  nr_ksymbol_events ; 
 int /*<<< orphan*/  nr_mmap_events ; 
 int /*<<< orphan*/  nr_namespaces_events ; 
 int /*<<< orphan*/  nr_switch_events ; 
 int /*<<< orphan*/  nr_task_events ; 
 int /*<<< orphan*/  perf_sched_count ; 
 int /*<<< orphan*/  perf_sched_events ; 
 int /*<<< orphan*/  perf_sched_mutex ; 
 int /*<<< orphan*/  static_branch_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void account_event(struct perf_event *event)
{
	bool inc = false;

	if (event->parent)
		return;

	if (event->attach_state & PERF_ATTACH_TASK)
		inc = true;
	if (event->attr.mmap || event->attr.mmap_data)
		atomic_inc(&nr_mmap_events);
	if (event->attr.comm)
		atomic_inc(&nr_comm_events);
	if (event->attr.namespaces)
		atomic_inc(&nr_namespaces_events);
	if (event->attr.task)
		atomic_inc(&nr_task_events);
	if (event->attr.freq)
		account_freq_event();
	if (event->attr.context_switch) {
		atomic_inc(&nr_switch_events);
		inc = true;
	}
	if (has_branch_stack(event))
		inc = true;
	if (is_cgroup_event(event))
		inc = true;
	if (event->attr.ksymbol)
		atomic_inc(&nr_ksymbol_events);
	if (event->attr.bpf_event)
		atomic_inc(&nr_bpf_events);

	if (inc) {
		/*
		 * We need the mutex here because static_branch_enable()
		 * must complete *before* the perf_sched_count increment
		 * becomes visible.
		 */
		if (atomic_inc_not_zero(&perf_sched_count))
			goto enabled;

		mutex_lock(&perf_sched_mutex);
		if (!atomic_read(&perf_sched_count)) {
			static_branch_enable(&perf_sched_events);
			/*
			 * Guarantee that all CPUs observe they key change and
			 * call the perf scheduling hooks before proceeding to
			 * install events that need them.
			 */
			synchronize_rcu();
		}
		/*
		 * Now that we have waited for the sync_sched(), allow further
		 * increments to by-pass the mutex.
		 */
		atomic_inc(&perf_sched_count);
		mutex_unlock(&perf_sched_mutex);
	}
enabled:

	account_event_cpu(event, event->cpu);

	account_pmu_sb_event(event);
}