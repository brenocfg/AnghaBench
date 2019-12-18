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
struct srcu_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_mb () ; 
 unsigned long srcu_readers_lock_idx (struct srcu_struct*,int) ; 
 unsigned long srcu_readers_unlock_idx (struct srcu_struct*,int) ; 

__attribute__((used)) static bool srcu_readers_active_idx_check(struct srcu_struct *ssp, int idx)
{
	unsigned long unlocks;

	unlocks = srcu_readers_unlock_idx(ssp, idx);

	/*
	 * Make sure that a lock is always counted if the corresponding
	 * unlock is counted. Needs to be a smp_mb() as the read side may
	 * contain a read from a variable that is written to before the
	 * synchronize_srcu() in the write side. In this case smp_mb()s
	 * A and B act like the store buffering pattern.
	 *
	 * This smp_mb() also pairs with smp_mb() C to prevent accesses
	 * after the synchronize_srcu() from being executed before the
	 * grace period ends.
	 */
	smp_mb(); /* A */

	/*
	 * If the locks are the same as the unlocks, then there must have
	 * been no readers on this index at some time in between. This does
	 * not mean that there are no more readers, as one could have read
	 * the current index but not have incremented the lock counter yet.
	 *
	 * So suppose that the updater is preempted here for so long
	 * that more than ULONG_MAX non-nested readers come and go in
	 * the meantime.  It turns out that this cannot result in overflow
	 * because if a reader modifies its unlock count after we read it
	 * above, then that reader's next load of ->srcu_idx is guaranteed
	 * to get the new value, which will cause it to operate on the
	 * other bank of counters, where it cannot contribute to the
	 * overflow of these counters.  This means that there is a maximum
	 * of 2*NR_CPUS increments, which cannot overflow given current
	 * systems, especially not on 64-bit systems.
	 *
	 * OK, how about nesting?  This does impose a limit on nesting
	 * of floor(ULONG_MAX/NR_CPUS/2), which should be sufficient,
	 * especially on 64-bit systems.
	 */
	return srcu_readers_lock_idx(ssp, idx) == unlocks;
}