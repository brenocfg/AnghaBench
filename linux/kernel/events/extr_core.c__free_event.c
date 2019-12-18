#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ target; } ;
struct TYPE_4__ {int sample_type; } ;
struct perf_event {int /*<<< orphan*/  rcu_head; TYPE_3__* pmu; scalar_t__ ctx; TYPE_2__ hw; int /*<<< orphan*/  (* destroy ) (struct perf_event*) ;int /*<<< orphan*/  addr_filter_ranges; TYPE_1__ attr; int /*<<< orphan*/  parent; int /*<<< orphan*/  mmap_mutex; scalar_t__ rb; int /*<<< orphan*/  pending; } ;
struct TYPE_6__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int PERF_SAMPLE_CALLCHAIN ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exclusive_event_destroy (struct perf_event*) ; 
 int /*<<< orphan*/  free_event_rcu ; 
 int /*<<< orphan*/  irq_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ is_cgroup_event (struct perf_event*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_addr_filters_splice (struct perf_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_detach_cgroup (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_free_bpf_prog (struct perf_event*) ; 
 int /*<<< orphan*/  put_callchain_buffers () ; 
 int /*<<< orphan*/  put_ctx (scalar_t__) ; 
 int /*<<< orphan*/  put_task_struct (scalar_t__) ; 
 int /*<<< orphan*/  ring_buffer_attach (struct perf_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 int /*<<< orphan*/  unaccount_event (struct perf_event*) ; 

__attribute__((used)) static void _free_event(struct perf_event *event)
{
	irq_work_sync(&event->pending);

	unaccount_event(event);

	if (event->rb) {
		/*
		 * Can happen when we close an event with re-directed output.
		 *
		 * Since we have a 0 refcount, perf_mmap_close() will skip
		 * over us; possibly making our ring_buffer_put() the last.
		 */
		mutex_lock(&event->mmap_mutex);
		ring_buffer_attach(event, NULL);
		mutex_unlock(&event->mmap_mutex);
	}

	if (is_cgroup_event(event))
		perf_detach_cgroup(event);

	if (!event->parent) {
		if (event->attr.sample_type & PERF_SAMPLE_CALLCHAIN)
			put_callchain_buffers();
	}

	perf_event_free_bpf_prog(event);
	perf_addr_filters_splice(event, NULL);
	kfree(event->addr_filter_ranges);

	if (event->destroy)
		event->destroy(event);

	/*
	 * Must be after ->destroy(), due to uprobe_perf_close() using
	 * hw.target.
	 */
	if (event->hw.target)
		put_task_struct(event->hw.target);

	/*
	 * perf_event_free_task() relies on put_ctx() being 'last', in particular
	 * all task references must be cleaned up.
	 */
	if (event->ctx)
		put_ctx(event->ctx);

	exclusive_event_destroy(event);
	module_put(event->pmu->module);

	call_rcu(&event->rcu_head, free_event_rcu);
}