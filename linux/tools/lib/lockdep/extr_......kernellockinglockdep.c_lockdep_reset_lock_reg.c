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
struct pending_free {int dummy; } ;
struct lockdep_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lockdep_reset_lock (struct pending_free*,struct lockdep_map*) ; 
 int /*<<< orphan*/  call_rcu_zapped (struct pending_free*) ; 
 struct pending_free* get_pending_free () ; 
 int graph_lock () ; 
 int /*<<< orphan*/  graph_unlock () ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 

__attribute__((used)) static void lockdep_reset_lock_reg(struct lockdep_map *lock)
{
	struct pending_free *pf;
	unsigned long flags;
	int locked;

	raw_local_irq_save(flags);
	locked = graph_lock();
	if (!locked)
		goto out_irq;

	pf = get_pending_free();
	__lockdep_reset_lock(pf, lock);
	call_rcu_zapped(pf);

	graph_unlock();
out_irq:
	raw_local_irq_restore(flags);
}