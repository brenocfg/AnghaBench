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
typedef  void* u64 ;
struct task_struct {int dummy; } ;
struct pmu {int /*<<< orphan*/  task_ctx_size; } ;
struct perf_event_context {int /*<<< orphan*/  lock; scalar_t__ task_ctx_data; } ;
struct hw_perf_event {int /*<<< orphan*/  period_left; void* last_period; void* sample_period; } ;
struct TYPE_2__ {scalar_t__ freq; } ;
struct perf_event {int state; int attach_state; int /*<<< orphan*/  child_mutex; int /*<<< orphan*/  child_list; int /*<<< orphan*/  overflow_handler_context; int /*<<< orphan*/  overflow_handler; struct perf_event_context* ctx; struct hw_perf_event hw; TYPE_1__ attr; int /*<<< orphan*/  refcount; struct pmu* pmu; int /*<<< orphan*/  cpu; struct perf_event* parent; } ;
typedef  enum perf_event_state { ____Placeholder_perf_event_state } perf_event_state ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct perf_event*) ; 
 int PERF_ATTACH_TASK_DATA ; 
 int PERF_EVENT_STATE_INACTIVE ; 
 int PERF_EVENT_STATE_OFF ; 
 int /*<<< orphan*/  add_event_to_ctx (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  atomic_long_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_event (struct perf_event*) ; 
 int /*<<< orphan*/  get_ctx (struct perf_event_context*) ; 
 scalar_t__ is_orphaned_event (struct perf_event*) ; 
 scalar_t__ kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event__header_size (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event__id_header_size (struct perf_event*) ; 
 struct perf_event* perf_event_alloc (TYPE_1__*,int /*<<< orphan*/ ,struct task_struct*,struct perf_event*,struct perf_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct perf_event *
inherit_event(struct perf_event *parent_event,
	      struct task_struct *parent,
	      struct perf_event_context *parent_ctx,
	      struct task_struct *child,
	      struct perf_event *group_leader,
	      struct perf_event_context *child_ctx)
{
	enum perf_event_state parent_state = parent_event->state;
	struct perf_event *child_event;
	unsigned long flags;

	/*
	 * Instead of creating recursive hierarchies of events,
	 * we link inherited events back to the original parent,
	 * which has a filp for sure, which we use as the reference
	 * count:
	 */
	if (parent_event->parent)
		parent_event = parent_event->parent;

	child_event = perf_event_alloc(&parent_event->attr,
					   parent_event->cpu,
					   child,
					   group_leader, parent_event,
					   NULL, NULL, -1);
	if (IS_ERR(child_event))
		return child_event;


	if ((child_event->attach_state & PERF_ATTACH_TASK_DATA) &&
	    !child_ctx->task_ctx_data) {
		struct pmu *pmu = child_event->pmu;

		child_ctx->task_ctx_data = kzalloc(pmu->task_ctx_size,
						   GFP_KERNEL);
		if (!child_ctx->task_ctx_data) {
			free_event(child_event);
			return NULL;
		}
	}

	/*
	 * is_orphaned_event() and list_add_tail(&parent_event->child_list)
	 * must be under the same lock in order to serialize against
	 * perf_event_release_kernel(), such that either we must observe
	 * is_orphaned_event() or they will observe us on the child_list.
	 */
	mutex_lock(&parent_event->child_mutex);
	if (is_orphaned_event(parent_event) ||
	    !atomic_long_inc_not_zero(&parent_event->refcount)) {
		mutex_unlock(&parent_event->child_mutex);
		/* task_ctx_data is freed with child_ctx */
		free_event(child_event);
		return NULL;
	}

	get_ctx(child_ctx);

	/*
	 * Make the child state follow the state of the parent event,
	 * not its attr.disabled bit.  We hold the parent's mutex,
	 * so we won't race with perf_event_{en, dis}able_family.
	 */
	if (parent_state >= PERF_EVENT_STATE_INACTIVE)
		child_event->state = PERF_EVENT_STATE_INACTIVE;
	else
		child_event->state = PERF_EVENT_STATE_OFF;

	if (parent_event->attr.freq) {
		u64 sample_period = parent_event->hw.sample_period;
		struct hw_perf_event *hwc = &child_event->hw;

		hwc->sample_period = sample_period;
		hwc->last_period   = sample_period;

		local64_set(&hwc->period_left, sample_period);
	}

	child_event->ctx = child_ctx;
	child_event->overflow_handler = parent_event->overflow_handler;
	child_event->overflow_handler_context
		= parent_event->overflow_handler_context;

	/*
	 * Precalculate sample_data sizes
	 */
	perf_event__header_size(child_event);
	perf_event__id_header_size(child_event);

	/*
	 * Link it up in the child's context:
	 */
	raw_spin_lock_irqsave(&child_ctx->lock, flags);
	add_event_to_ctx(child_event, child_ctx);
	raw_spin_unlock_irqrestore(&child_ctx->lock, flags);

	/*
	 * Link this into the parent event's child list
	 */
	list_add_tail(&child_event->child_list, &parent_event->child_list);
	mutex_unlock(&parent_event->child_mutex);

	return child_event;
}