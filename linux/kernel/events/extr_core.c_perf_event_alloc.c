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
struct task_struct {int dummy; } ;
struct pmu {int capabilities; int nr_addr_filters; int /*<<< orphan*/  module; } ;
struct perf_event_attr {int sample_period; int sample_type; int /*<<< orphan*/  sample_max_stack; scalar_t__ aux_output; scalar_t__ branch_sample_type; scalar_t__ inherit; scalar_t__ sample_freq; scalar_t__ freq; } ;
struct hw_perf_event {int sample_period; int last_period; scalar_t__ target; int /*<<< orphan*/  period_left; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct perf_event {int pending_disable; int cpu; int oncpu; scalar_t__ overflow_handler; int addr_filters_gen; struct hw_perf_event hw; scalar_t__ ns; int /*<<< orphan*/  (* destroy ) (struct perf_event*) ;struct perf_event* addr_filter_ranges; struct perf_event_attr attr; struct perf_event* parent; int /*<<< orphan*/ * overflow_handler_context; int /*<<< orphan*/  orig_overflow_handler; struct pmu* prog; int /*<<< orphan*/ * clock; int /*<<< orphan*/  attach_state; int /*<<< orphan*/  state; int /*<<< orphan*/  id; int /*<<< orphan*/ * pmu; struct perf_event* group_leader; int /*<<< orphan*/  refcount; TYPE_1__ addr_filters; int /*<<< orphan*/  mmap_mutex; int /*<<< orphan*/  pending; int /*<<< orphan*/  waitq; int /*<<< orphan*/  hlist_entry; int /*<<< orphan*/  active_entry; int /*<<< orphan*/  rb_entry; int /*<<< orphan*/  active_list; int /*<<< orphan*/  sibling_list; int /*<<< orphan*/  event_entry; int /*<<< orphan*/  child_list; int /*<<< orphan*/  child_mutex; } ;
struct perf_addr_filters_head {int /*<<< orphan*/  lock; } ;
struct perf_addr_filter_range {int dummy; } ;
struct bpf_prog {int capabilities; int nr_addr_filters; int /*<<< orphan*/  module; } ;
typedef  scalar_t__ perf_overflow_handler_t ;

/* Variables and functions */
 long EINVAL ; 
 long ENOMEM ; 
 long EOPNOTSUPP ; 
 struct perf_event* ERR_PTR (long) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct pmu*) ; 
 int /*<<< orphan*/  PERF_ATTACH_TASK ; 
 int /*<<< orphan*/  PERF_EVENT_STATE_INACTIVE ; 
 int PERF_PMU_CAP_AUX_OUTPUT ; 
 int PERF_SAMPLE_CALLCHAIN ; 
 int PERF_SAMPLE_READ ; 
 long PTR_ERR (struct pmu*) ; 
 int /*<<< orphan*/  account_event (struct perf_event*) ; 
 int /*<<< orphan*/  atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bpf_overflow_handler ; 
 struct pmu* bpf_prog_inc (struct pmu*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  exclusive_event_destroy (struct perf_event*) ; 
 long exclusive_event_init (struct perf_event*) ; 
 long get_callchain_buffers (int /*<<< orphan*/ ) ; 
 scalar_t__ get_pid_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ get_task_struct (struct task_struct*) ; 
 scalar_t__ has_addr_filter (struct perf_event*) ; 
 int /*<<< orphan*/  has_branch_stack (struct perf_event*) ; 
 int /*<<< orphan*/  init_event_group (struct perf_event*) ; 
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ is_cgroup_event (struct perf_event*) ; 
 scalar_t__ is_write_backward (struct perf_event*) ; 
 struct perf_event* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct perf_event*) ; 
 struct perf_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  local_clock ; 
 int /*<<< orphan*/  memcpy (struct perf_event*,struct perf_event*,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 unsigned int nr_cpu_ids ; 
 long perf_cgroup_connect (int,struct perf_event*,struct perf_event_attr*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_detach_cgroup (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event__state_init (struct perf_event*) ; 
 struct perf_addr_filters_head* perf_event_addr_filters (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_id ; 
 scalar_t__ perf_event_output_backward ; 
 scalar_t__ perf_event_output_forward ; 
 struct pmu* perf_init_event (struct perf_event*) ; 
 int /*<<< orphan*/  perf_pending_event ; 
 int /*<<< orphan*/  put_pid_ns (scalar_t__) ; 
 int /*<<< orphan*/  put_task_struct (scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 int /*<<< orphan*/  task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct perf_event *
perf_event_alloc(struct perf_event_attr *attr, int cpu,
		 struct task_struct *task,
		 struct perf_event *group_leader,
		 struct perf_event *parent_event,
		 perf_overflow_handler_t overflow_handler,
		 void *context, int cgroup_fd)
{
	struct pmu *pmu;
	struct perf_event *event;
	struct hw_perf_event *hwc;
	long err = -EINVAL;

	if ((unsigned)cpu >= nr_cpu_ids) {
		if (!task || cpu != -1)
			return ERR_PTR(-EINVAL);
	}

	event = kzalloc(sizeof(*event), GFP_KERNEL);
	if (!event)
		return ERR_PTR(-ENOMEM);

	/*
	 * Single events are their own group leaders, with an
	 * empty sibling list:
	 */
	if (!group_leader)
		group_leader = event;

	mutex_init(&event->child_mutex);
	INIT_LIST_HEAD(&event->child_list);

	INIT_LIST_HEAD(&event->event_entry);
	INIT_LIST_HEAD(&event->sibling_list);
	INIT_LIST_HEAD(&event->active_list);
	init_event_group(event);
	INIT_LIST_HEAD(&event->rb_entry);
	INIT_LIST_HEAD(&event->active_entry);
	INIT_LIST_HEAD(&event->addr_filters.list);
	INIT_HLIST_NODE(&event->hlist_entry);


	init_waitqueue_head(&event->waitq);
	event->pending_disable = -1;
	init_irq_work(&event->pending, perf_pending_event);

	mutex_init(&event->mmap_mutex);
	raw_spin_lock_init(&event->addr_filters.lock);

	atomic_long_set(&event->refcount, 1);
	event->cpu		= cpu;
	event->attr		= *attr;
	event->group_leader	= group_leader;
	event->pmu		= NULL;
	event->oncpu		= -1;

	event->parent		= parent_event;

	event->ns		= get_pid_ns(task_active_pid_ns(current));
	event->id		= atomic64_inc_return(&perf_event_id);

	event->state		= PERF_EVENT_STATE_INACTIVE;

	if (task) {
		event->attach_state = PERF_ATTACH_TASK;
		/*
		 * XXX pmu::event_init needs to know what task to account to
		 * and we cannot use the ctx information because we need the
		 * pmu before we get a ctx.
		 */
		event->hw.target = get_task_struct(task);
	}

	event->clock = &local_clock;
	if (parent_event)
		event->clock = parent_event->clock;

	if (!overflow_handler && parent_event) {
		overflow_handler = parent_event->overflow_handler;
		context = parent_event->overflow_handler_context;
#if defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_EVENT_TRACING)
		if (overflow_handler == bpf_overflow_handler) {
			struct bpf_prog *prog = bpf_prog_inc(parent_event->prog);

			if (IS_ERR(prog)) {
				err = PTR_ERR(prog);
				goto err_ns;
			}
			event->prog = prog;
			event->orig_overflow_handler =
				parent_event->orig_overflow_handler;
		}
#endif
	}

	if (overflow_handler) {
		event->overflow_handler	= overflow_handler;
		event->overflow_handler_context = context;
	} else if (is_write_backward(event)){
		event->overflow_handler = perf_event_output_backward;
		event->overflow_handler_context = NULL;
	} else {
		event->overflow_handler = perf_event_output_forward;
		event->overflow_handler_context = NULL;
	}

	perf_event__state_init(event);

	pmu = NULL;

	hwc = &event->hw;
	hwc->sample_period = attr->sample_period;
	if (attr->freq && attr->sample_freq)
		hwc->sample_period = 1;
	hwc->last_period = hwc->sample_period;

	local64_set(&hwc->period_left, hwc->sample_period);

	/*
	 * We currently do not support PERF_SAMPLE_READ on inherited events.
	 * See perf_output_read().
	 */
	if (attr->inherit && (attr->sample_type & PERF_SAMPLE_READ))
		goto err_ns;

	if (!has_branch_stack(event))
		event->attr.branch_sample_type = 0;

	if (cgroup_fd != -1) {
		err = perf_cgroup_connect(cgroup_fd, event, attr, group_leader);
		if (err)
			goto err_ns;
	}

	pmu = perf_init_event(event);
	if (IS_ERR(pmu)) {
		err = PTR_ERR(pmu);
		goto err_ns;
	}

	if (event->attr.aux_output &&
	    !(pmu->capabilities & PERF_PMU_CAP_AUX_OUTPUT)) {
		err = -EOPNOTSUPP;
		goto err_pmu;
	}

	err = exclusive_event_init(event);
	if (err)
		goto err_pmu;

	if (has_addr_filter(event)) {
		event->addr_filter_ranges = kcalloc(pmu->nr_addr_filters,
						    sizeof(struct perf_addr_filter_range),
						    GFP_KERNEL);
		if (!event->addr_filter_ranges) {
			err = -ENOMEM;
			goto err_per_task;
		}

		/*
		 * Clone the parent's vma offsets: they are valid until exec()
		 * even if the mm is not shared with the parent.
		 */
		if (event->parent) {
			struct perf_addr_filters_head *ifh = perf_event_addr_filters(event);

			raw_spin_lock_irq(&ifh->lock);
			memcpy(event->addr_filter_ranges,
			       event->parent->addr_filter_ranges,
			       pmu->nr_addr_filters * sizeof(struct perf_addr_filter_range));
			raw_spin_unlock_irq(&ifh->lock);
		}

		/* force hw sync on the address filters */
		event->addr_filters_gen = 1;
	}

	if (!event->parent) {
		if (event->attr.sample_type & PERF_SAMPLE_CALLCHAIN) {
			err = get_callchain_buffers(attr->sample_max_stack);
			if (err)
				goto err_addr_filters;
		}
	}

	/* symmetric to unaccount_event() in _free_event() */
	account_event(event);

	return event;

err_addr_filters:
	kfree(event->addr_filter_ranges);

err_per_task:
	exclusive_event_destroy(event);

err_pmu:
	if (event->destroy)
		event->destroy(event);
	module_put(pmu->module);
err_ns:
	if (is_cgroup_event(event))
		perf_detach_cgroup(event);
	if (event->ns)
		put_pid_ns(event->ns);
	if (event->hw.target)
		put_task_struct(event->hw.target);
	kfree(event);

	return ERR_PTR(err);
}