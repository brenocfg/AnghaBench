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
struct upid {int nr; struct pid_namespace* ns; } ;
struct pid_namespace {int level; int pid_allocated; int /*<<< orphan*/  pid_cachep; int /*<<< orphan*/  idr; struct pid_namespace* parent; } ;
struct pid {int level; struct upid* numbers; int /*<<< orphan*/  wait_pidfd; int /*<<< orphan*/ * tasks; int /*<<< orphan*/  count; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct pid* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int PIDNS_ADDING ; 
 int PIDTYPE_MAX ; 
 int RESERVED_PIDS ; 
 int /*<<< orphan*/  get_pid_ns (struct pid_namespace*) ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int idr_get_cursor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,struct pid*,int) ; 
 int /*<<< orphan*/  idr_set_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_child_reaper (struct pid*) ; 
 struct pid* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct pid*) ; 
 int /*<<< orphan*/  pid_max ; 
 scalar_t__ pid_ns_prepare_proc (struct pid_namespace*) ; 
 int /*<<< orphan*/  pidmap_lock ; 
 int /*<<< orphan*/  put_pid_ns (struct pid_namespace*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct pid *alloc_pid(struct pid_namespace *ns)
{
	struct pid *pid;
	enum pid_type type;
	int i, nr;
	struct pid_namespace *tmp;
	struct upid *upid;
	int retval = -ENOMEM;

	pid = kmem_cache_alloc(ns->pid_cachep, GFP_KERNEL);
	if (!pid)
		return ERR_PTR(retval);

	tmp = ns;
	pid->level = ns->level;

	for (i = ns->level; i >= 0; i--) {
		int pid_min = 1;

		idr_preload(GFP_KERNEL);
		spin_lock_irq(&pidmap_lock);

		/*
		 * init really needs pid 1, but after reaching the maximum
		 * wrap back to RESERVED_PIDS
		 */
		if (idr_get_cursor(&tmp->idr) > RESERVED_PIDS)
			pid_min = RESERVED_PIDS;

		/*
		 * Store a null pointer so find_pid_ns does not find
		 * a partially initialized PID (see below).
		 */
		nr = idr_alloc_cyclic(&tmp->idr, NULL, pid_min,
				      pid_max, GFP_ATOMIC);
		spin_unlock_irq(&pidmap_lock);
		idr_preload_end();

		if (nr < 0) {
			retval = (nr == -ENOSPC) ? -EAGAIN : nr;
			goto out_free;
		}

		pid->numbers[i].nr = nr;
		pid->numbers[i].ns = tmp;
		tmp = tmp->parent;
	}

	if (unlikely(is_child_reaper(pid))) {
		if (pid_ns_prepare_proc(ns))
			goto out_free;
	}

	get_pid_ns(ns);
	refcount_set(&pid->count, 1);
	for (type = 0; type < PIDTYPE_MAX; ++type)
		INIT_HLIST_HEAD(&pid->tasks[type]);

	init_waitqueue_head(&pid->wait_pidfd);

	upid = pid->numbers + ns->level;
	spin_lock_irq(&pidmap_lock);
	if (!(ns->pid_allocated & PIDNS_ADDING))
		goto out_unlock;
	for ( ; upid >= pid->numbers; --upid) {
		/* Make the PID visible to find_pid_ns. */
		idr_replace(&upid->ns->idr, pid, upid->nr);
		upid->ns->pid_allocated++;
	}
	spin_unlock_irq(&pidmap_lock);

	return pid;

out_unlock:
	spin_unlock_irq(&pidmap_lock);
	put_pid_ns(ns);

out_free:
	spin_lock_irq(&pidmap_lock);
	while (++i <= ns->level) {
		upid = pid->numbers + i;
		idr_remove(&upid->ns->idr, upid->nr);
	}

	/* On failure to allocate the first pid, reset the state */
	if (ns->pid_allocated == PIDNS_ADDING)
		idr_set_cursor(&ns->idr, 0);

	spin_unlock_irq(&pidmap_lock);

	kmem_cache_free(ns->pid_cachep, pid);
	return ERR_PTR(retval);
}