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
struct workqueue_struct {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  cpu_pwqs; } ;
struct list_head {int dummy; } ;
struct worker_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  watchdog_ts; struct list_head worklist; } ;
struct worker {struct pool_workqueue* current_pwq; } ;
struct work_struct {struct list_head entry; } ;
struct pool_workqueue {size_t work_color; scalar_t__ nr_active; scalar_t__ max_active; struct worker_pool* pool; struct list_head delayed_works; int /*<<< orphan*/ * nr_in_flight; int /*<<< orphan*/  refcnt; struct workqueue_struct* wq; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 unsigned int WORK_CPU_UNBOUND ; 
 unsigned int WORK_STRUCT_DELAYED ; 
 int WQ_UNBOUND ; 
 int __WQ_DRAINING ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  debug_work_activate (struct work_struct*) ; 
 struct worker* find_worker_executing_work (struct worker_pool*,struct work_struct*) ; 
 struct worker_pool* get_work_pool (struct work_struct*) ; 
 int /*<<< orphan*/  insert_work (struct pool_workqueue*,struct work_struct*,struct list_head*,unsigned int) ; 
 int /*<<< orphan*/  is_chained_work (struct workqueue_struct*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (int) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 struct pool_workqueue* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_workqueue_activate_work (struct work_struct*) ; 
 int /*<<< orphan*/  trace_workqueue_queue_work (unsigned int,struct pool_workqueue*,struct work_struct*) ; 
 struct pool_workqueue* unbound_pwq_by_node (struct workqueue_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 unsigned int work_color_to_flags (size_t) ; 
 int wq_select_unbound_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __queue_work(int cpu, struct workqueue_struct *wq,
			 struct work_struct *work)
{
	struct pool_workqueue *pwq;
	struct worker_pool *last_pool;
	struct list_head *worklist;
	unsigned int work_flags;
	unsigned int req_cpu = cpu;

	/*
	 * While a work item is PENDING && off queue, a task trying to
	 * steal the PENDING will busy-loop waiting for it to either get
	 * queued or lose PENDING.  Grabbing PENDING and queueing should
	 * happen with IRQ disabled.
	 */
	lockdep_assert_irqs_disabled();

	debug_work_activate(work);

	/* if draining, only works from the same workqueue are allowed */
	if (unlikely(wq->flags & __WQ_DRAINING) &&
	    WARN_ON_ONCE(!is_chained_work(wq)))
		return;
	rcu_read_lock();
retry:
	if (req_cpu == WORK_CPU_UNBOUND)
		cpu = wq_select_unbound_cpu(raw_smp_processor_id());

	/* pwq which will be used unless @work is executing elsewhere */
	if (!(wq->flags & WQ_UNBOUND))
		pwq = per_cpu_ptr(wq->cpu_pwqs, cpu);
	else
		pwq = unbound_pwq_by_node(wq, cpu_to_node(cpu));

	/*
	 * If @work was previously on a different pool, it might still be
	 * running there, in which case the work needs to be queued on that
	 * pool to guarantee non-reentrancy.
	 */
	last_pool = get_work_pool(work);
	if (last_pool && last_pool != pwq->pool) {
		struct worker *worker;

		spin_lock(&last_pool->lock);

		worker = find_worker_executing_work(last_pool, work);

		if (worker && worker->current_pwq->wq == wq) {
			pwq = worker->current_pwq;
		} else {
			/* meh... not running there, queue here */
			spin_unlock(&last_pool->lock);
			spin_lock(&pwq->pool->lock);
		}
	} else {
		spin_lock(&pwq->pool->lock);
	}

	/*
	 * pwq is determined and locked.  For unbound pools, we could have
	 * raced with pwq release and it could already be dead.  If its
	 * refcnt is zero, repeat pwq selection.  Note that pwqs never die
	 * without another pwq replacing it in the numa_pwq_tbl or while
	 * work items are executing on it, so the retrying is guaranteed to
	 * make forward-progress.
	 */
	if (unlikely(!pwq->refcnt)) {
		if (wq->flags & WQ_UNBOUND) {
			spin_unlock(&pwq->pool->lock);
			cpu_relax();
			goto retry;
		}
		/* oops */
		WARN_ONCE(true, "workqueue: per-cpu pwq for %s on cpu%d has 0 refcnt",
			  wq->name, cpu);
	}

	/* pwq determined, queue */
	trace_workqueue_queue_work(req_cpu, pwq, work);

	if (WARN_ON(!list_empty(&work->entry)))
		goto out;

	pwq->nr_in_flight[pwq->work_color]++;
	work_flags = work_color_to_flags(pwq->work_color);

	if (likely(pwq->nr_active < pwq->max_active)) {
		trace_workqueue_activate_work(work);
		pwq->nr_active++;
		worklist = &pwq->pool->worklist;
		if (list_empty(worklist))
			pwq->pool->watchdog_ts = jiffies;
	} else {
		work_flags |= WORK_STRUCT_DELAYED;
		worklist = &pwq->delayed_works;
	}

	insert_work(pwq, work, worklist, work_flags);

out:
	spin_unlock(&pwq->pool->lock);
	rcu_read_unlock();
}