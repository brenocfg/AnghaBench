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
struct mem_cgroup {unsigned long move_lock_flags; int /*<<< orphan*/  move_lock; int /*<<< orphan*/ * move_lock_task; } ;

/* Variables and functions */
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void __unlock_page_memcg(struct mem_cgroup *memcg)
{
	if (memcg && memcg->move_lock_task == current) {
		unsigned long flags = memcg->move_lock_flags;

		memcg->move_lock_task = NULL;
		memcg->move_lock_flags = 0;

		spin_unlock_irqrestore(&memcg->move_lock, flags);
	}

	rcu_read_unlock();
}