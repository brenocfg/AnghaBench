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
struct worker_pool {int /*<<< orphan*/  nr_running; } ;
struct worker {scalar_t__ task; unsigned int flags; struct worker_pool* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 unsigned int WORKER_NOT_RUNNING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ current ; 

__attribute__((used)) static inline void worker_set_flags(struct worker *worker, unsigned int flags)
{
	struct worker_pool *pool = worker->pool;

	WARN_ON_ONCE(worker->task != current);

	/* If transitioning into NOT_RUNNING, adjust nr_running. */
	if ((flags & WORKER_NOT_RUNNING) &&
	    !(worker->flags & WORKER_NOT_RUNNING)) {
		atomic_dec(&pool->nr_running);
	}

	worker->flags |= flags;
}