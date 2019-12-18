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
struct srcu_struct {scalar_t__ srcu_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void srcu_flip(struct srcu_struct *ssp)
{
	/*
	 * Ensure that if this updater saw a given reader's increment
	 * from __srcu_read_lock(), that reader was using an old value
	 * of ->srcu_idx.  Also ensure that if a given reader sees the
	 * new value of ->srcu_idx, this updater's earlier scans cannot
	 * have seen that reader's increments (which is OK, because this
	 * grace period need not wait on that reader).
	 */
	smp_mb(); /* E */  /* Pairs with B and C. */

	WRITE_ONCE(ssp->srcu_idx, ssp->srcu_idx + 1);

	/*
	 * Ensure that if the updater misses an __srcu_read_unlock()
	 * increment, that task's next __srcu_read_lock() will see the
	 * above counter update.  Note that both this memory barrier
	 * and the one in srcu_readers_active_idx_check() provide the
	 * guarantee for __srcu_read_lock().
	 */
	smp_mb(); /* D */  /* Pairs with C. */
}