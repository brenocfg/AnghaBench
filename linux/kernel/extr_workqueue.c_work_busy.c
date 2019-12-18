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
struct work_struct {int dummy; } ;

/* Variables and functions */
 unsigned int WORK_BUSY_PENDING ; 
 unsigned int WORK_BUSY_RUNNING ; 
 scalar_t__ find_worker_executing_work (struct worker_pool*,struct work_struct*) ; 
 struct worker_pool* get_work_pool (struct work_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ work_pending (struct work_struct*) ; 

unsigned int work_busy(struct work_struct *work)
{
	struct worker_pool *pool;
	unsigned long flags;
	unsigned int ret = 0;

	if (work_pending(work))
		ret |= WORK_BUSY_PENDING;

	rcu_read_lock();
	pool = get_work_pool(work);
	if (pool) {
		spin_lock_irqsave(&pool->lock, flags);
		if (find_worker_executing_work(pool, work))
			ret |= WORK_BUSY_RUNNING;
		spin_unlock_irqrestore(&pool->lock, flags);
	}
	rcu_read_unlock();

	return ret;
}