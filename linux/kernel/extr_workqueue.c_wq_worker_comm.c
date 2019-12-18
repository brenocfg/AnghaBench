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
struct worker_pool {int /*<<< orphan*/  lock; } ;
struct worker {char* desc; scalar_t__ current_work; struct worker_pool* pool; } ;
struct task_struct {int flags; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int PF_WQ_WORKER ; 
 struct worker* kthread_data (struct task_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int strscpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wq_pool_attach_mutex ; 

void wq_worker_comm(char *buf, size_t size, struct task_struct *task)
{
	int off;

	/* always show the actual comm */
	off = strscpy(buf, task->comm, size);
	if (off < 0)
		return;

	/* stabilize PF_WQ_WORKER and worker pool association */
	mutex_lock(&wq_pool_attach_mutex);

	if (task->flags & PF_WQ_WORKER) {
		struct worker *worker = kthread_data(task);
		struct worker_pool *pool = worker->pool;

		if (pool) {
			spin_lock_irq(&pool->lock);
			/*
			 * ->desc tracks information (wq name or
			 * set_worker_desc()) for the latest execution.  If
			 * current, prepend '+', otherwise '-'.
			 */
			if (worker->desc[0] != '\0') {
				if (worker->current_work)
					scnprintf(buf + off, size - off, "+%s",
						  worker->desc);
				else
					scnprintf(buf + off, size - off, "-%s",
						  worker->desc);
			}
			spin_unlock_irq(&pool->lock);
		}
	}

	mutex_unlock(&wq_pool_attach_mutex);
}