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
struct qlist_head {int dummy; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 struct qlist_head QLIST_INIT ; 
 unsigned long QUARANTINE_BATCHES ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/ * global_quarantine ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct kmem_cache*,int) ; 
 int /*<<< orphan*/  per_cpu_remove_cache ; 
 scalar_t__ qlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlist_free_all (struct qlist_head*,struct kmem_cache*) ; 
 int /*<<< orphan*/  qlist_move_cache (int /*<<< orphan*/ *,struct qlist_head*,struct kmem_cache*) ; 
 int /*<<< orphan*/  quarantine_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  remove_cache_srcu ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

void quarantine_remove_cache(struct kmem_cache *cache)
{
	unsigned long flags, i;
	struct qlist_head to_free = QLIST_INIT;

	/*
	 * Must be careful to not miss any objects that are being moved from
	 * per-cpu list to the global quarantine in quarantine_put(),
	 * nor objects being freed in quarantine_reduce(). on_each_cpu()
	 * achieves the first goal, while synchronize_srcu() achieves the
	 * second.
	 */
	on_each_cpu(per_cpu_remove_cache, cache, 1);

	raw_spin_lock_irqsave(&quarantine_lock, flags);
	for (i = 0; i < QUARANTINE_BATCHES; i++) {
		if (qlist_empty(&global_quarantine[i]))
			continue;
		qlist_move_cache(&global_quarantine[i], &to_free, cache);
		/* Scanning whole quarantine can take a while. */
		raw_spin_unlock_irqrestore(&quarantine_lock, flags);
		cond_resched();
		raw_spin_lock_irqsave(&quarantine_lock, flags);
	}
	raw_spin_unlock_irqrestore(&quarantine_lock, flags);

	qlist_free_all(&to_free, cache);

	synchronize_srcu(&remove_cache_srcu);
}