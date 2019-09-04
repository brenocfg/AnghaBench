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
struct task_struct {int flags; int /*<<< orphan*/  perf_event_mutex; scalar_t__* perf_event_ctxp; } ;
struct pmu {int task_ctx_nr; int /*<<< orphan*/  task_ctx_size; int /*<<< orphan*/  pmu_cpu_context; } ;
struct perf_event_context {int /*<<< orphan*/  pin_count; void* task_ctx_data; int /*<<< orphan*/  lock; } ;
struct perf_event {int cpu; int attach_state; } ;
struct perf_cpu_context {struct perf_event_context ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct perf_event_context* ERR_PTR (int) ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PERF_ATTACH_TASK_DATA ; 
 int PF_EXITING ; 
 struct perf_event_context* alloc_perf_context (struct pmu*,struct task_struct*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ctx (struct perf_event_context*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct perf_cpu_context* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 struct perf_event_context* perf_lock_task_context (struct task_struct*,int,unsigned long*) ; 
 scalar_t__ perf_paranoid_cpu () ; 
 int /*<<< orphan*/  put_ctx (struct perf_event_context*) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_assign_pointer (scalar_t__,struct perf_event_context*) ; 
 struct perf_event_context* unclone_ctx (struct perf_event_context*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct perf_event_context *
find_get_context(struct pmu *pmu, struct task_struct *task,
		struct perf_event *event)
{
	struct perf_event_context *ctx, *clone_ctx = NULL;
	struct perf_cpu_context *cpuctx;
	void *task_ctx_data = NULL;
	unsigned long flags;
	int ctxn, err;
	int cpu = event->cpu;

	if (!task) {
		/* Must be root to operate on a CPU event: */
		if (perf_paranoid_cpu() && !capable(CAP_SYS_ADMIN))
			return ERR_PTR(-EACCES);

		cpuctx = per_cpu_ptr(pmu->pmu_cpu_context, cpu);
		ctx = &cpuctx->ctx;
		get_ctx(ctx);
		++ctx->pin_count;

		return ctx;
	}

	err = -EINVAL;
	ctxn = pmu->task_ctx_nr;
	if (ctxn < 0)
		goto errout;

	if (event->attach_state & PERF_ATTACH_TASK_DATA) {
		task_ctx_data = kzalloc(pmu->task_ctx_size, GFP_KERNEL);
		if (!task_ctx_data) {
			err = -ENOMEM;
			goto errout;
		}
	}

retry:
	ctx = perf_lock_task_context(task, ctxn, &flags);
	if (ctx) {
		clone_ctx = unclone_ctx(ctx);
		++ctx->pin_count;

		if (task_ctx_data && !ctx->task_ctx_data) {
			ctx->task_ctx_data = task_ctx_data;
			task_ctx_data = NULL;
		}
		raw_spin_unlock_irqrestore(&ctx->lock, flags);

		if (clone_ctx)
			put_ctx(clone_ctx);
	} else {
		ctx = alloc_perf_context(pmu, task);
		err = -ENOMEM;
		if (!ctx)
			goto errout;

		if (task_ctx_data) {
			ctx->task_ctx_data = task_ctx_data;
			task_ctx_data = NULL;
		}

		err = 0;
		mutex_lock(&task->perf_event_mutex);
		/*
		 * If it has already passed perf_event_exit_task().
		 * we must see PF_EXITING, it takes this mutex too.
		 */
		if (task->flags & PF_EXITING)
			err = -ESRCH;
		else if (task->perf_event_ctxp[ctxn])
			err = -EAGAIN;
		else {
			get_ctx(ctx);
			++ctx->pin_count;
			rcu_assign_pointer(task->perf_event_ctxp[ctxn], ctx);
		}
		mutex_unlock(&task->perf_event_mutex);

		if (unlikely(err)) {
			put_ctx(ctx);

			if (err == -EAGAIN)
				goto retry;
			goto errout;
		}
	}

	kfree(task_ctx_data);
	return ctx;

errout:
	kfree(task_ctx_data);
	return ERR_PTR(err);
}