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
struct tracer {int /*<<< orphan*/  enabled; scalar_t__ init; scalar_t__ use_max_tr; int /*<<< orphan*/  (* reset ) (struct trace_array*) ;scalar_t__ ref; int /*<<< orphan*/  name; scalar_t__ noboot; struct tracer* next; } ;
struct trace_array {int allocated_snapshot; struct tracer* current_trace; int /*<<< orphan*/  max_lock; scalar_t__ cond_snapshot; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RING_BUFFER_ALL_CPUS ; 
 scalar_t__ SYSTEM_RUNNING ; 
 int __tracing_resize_ring_buffer (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_snapshot (struct trace_array*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tracer nop_trace ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_buffer_expanded ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (struct trace_array*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ system_state ; 
 int /*<<< orphan*/  trace_branch_disable () ; 
 int /*<<< orphan*/  trace_branch_enable (struct trace_array*) ; 
 int /*<<< orphan*/  trace_buf_size ; 
 int /*<<< orphan*/  trace_ok_for_array (struct tracer*,struct trace_array*) ; 
 struct tracer* trace_types ; 
 int /*<<< orphan*/  trace_types_lock ; 
 int tracer_init (struct tracer*,struct trace_array*) ; 
 int tracing_alloc_snapshot_instance (struct trace_array*) ; 

__attribute__((used)) static int tracing_set_tracer(struct trace_array *tr, const char *buf)
{
	struct tracer *t;
#ifdef CONFIG_TRACER_MAX_TRACE
	bool had_max_tr;
#endif
	int ret = 0;

	mutex_lock(&trace_types_lock);

	if (!ring_buffer_expanded) {
		ret = __tracing_resize_ring_buffer(tr, trace_buf_size,
						RING_BUFFER_ALL_CPUS);
		if (ret < 0)
			goto out;
		ret = 0;
	}

	for (t = trace_types; t; t = t->next) {
		if (strcmp(t->name, buf) == 0)
			break;
	}
	if (!t) {
		ret = -EINVAL;
		goto out;
	}
	if (t == tr->current_trace)
		goto out;

#ifdef CONFIG_TRACER_SNAPSHOT
	if (t->use_max_tr) {
		arch_spin_lock(&tr->max_lock);
		if (tr->cond_snapshot)
			ret = -EBUSY;
		arch_spin_unlock(&tr->max_lock);
		if (ret)
			goto out;
	}
#endif
	/* Some tracers won't work on kernel command line */
	if (system_state < SYSTEM_RUNNING && t->noboot) {
		pr_warn("Tracer '%s' is not allowed on command line, ignored\n",
			t->name);
		goto out;
	}

	/* Some tracers are only allowed for the top level buffer */
	if (!trace_ok_for_array(t, tr)) {
		ret = -EINVAL;
		goto out;
	}

	/* If trace pipe files are being read, we can't change the tracer */
	if (tr->current_trace->ref) {
		ret = -EBUSY;
		goto out;
	}

	trace_branch_disable();

	tr->current_trace->enabled--;

	if (tr->current_trace->reset)
		tr->current_trace->reset(tr);

	/* Current trace needs to be nop_trace before synchronize_rcu */
	tr->current_trace = &nop_trace;

#ifdef CONFIG_TRACER_MAX_TRACE
	had_max_tr = tr->allocated_snapshot;

	if (had_max_tr && !t->use_max_tr) {
		/*
		 * We need to make sure that the update_max_tr sees that
		 * current_trace changed to nop_trace to keep it from
		 * swapping the buffers after we resize it.
		 * The update_max_tr is called from interrupts disabled
		 * so a synchronized_sched() is sufficient.
		 */
		synchronize_rcu();
		free_snapshot(tr);
	}
#endif

#ifdef CONFIG_TRACER_MAX_TRACE
	if (t->use_max_tr && !had_max_tr) {
		ret = tracing_alloc_snapshot_instance(tr);
		if (ret < 0)
			goto out;
	}
#endif

	if (t->init) {
		ret = tracer_init(t, tr);
		if (ret)
			goto out;
	}

	tr->current_trace = t;
	tr->current_trace->enabled++;
	trace_branch_enable(tr);
 out:
	mutex_unlock(&trace_types_lock);

	return ret;
}