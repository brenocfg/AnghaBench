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
struct worker_pool {int /*<<< orphan*/  nr_idle; } ;
struct worker {int flags; int /*<<< orphan*/  entry; struct worker_pool* pool; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int WORKER_IDLE ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  worker_clr_flags (struct worker*,int) ; 

__attribute__((used)) static void worker_leave_idle(struct worker *worker)
{
	struct worker_pool *pool = worker->pool;

	if (WARN_ON_ONCE(!(worker->flags & WORKER_IDLE)))
		return;
	worker_clr_flags(worker, WORKER_IDLE);
	pool->nr_idle--;
	list_del_init(&worker->entry);
}