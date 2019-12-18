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
struct qlist_head {scalar_t__ bytes; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 struct qlist_head QLIST_INIT ; 
 int QUARANTINE_BATCHES ; 
 size_t QUARANTINE_FRACTION ; 
 size_t QUARANTINE_PERCPU_SIZE ; 
 scalar_t__ READ_ONCE (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * global_quarantine ; 
 scalar_t__ likely (int) ; 
 scalar_t__ max (size_t,int) ; 
 size_t num_online_cpus () ; 
 int /*<<< orphan*/  qlist_free_all (struct qlist_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlist_move_all (int /*<<< orphan*/ *,struct qlist_head*) ; 
 scalar_t__ quarantine_batch_size ; 
 size_t quarantine_head ; 
 int /*<<< orphan*/  quarantine_lock ; 
 scalar_t__ quarantine_max_size ; 
 scalar_t__ quarantine_size ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  remove_cache_srcu ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 size_t totalram_pages () ; 

void quarantine_reduce(void)
{
	size_t total_size, new_quarantine_size, percpu_quarantines;
	unsigned long flags;
	int srcu_idx;
	struct qlist_head to_free = QLIST_INIT;

	if (likely(READ_ONCE(quarantine_size) <=
		   READ_ONCE(quarantine_max_size)))
		return;

	/*
	 * srcu critical section ensures that quarantine_remove_cache()
	 * will not miss objects belonging to the cache while they are in our
	 * local to_free list. srcu is chosen because (1) it gives us private
	 * grace period domain that does not interfere with anything else,
	 * and (2) it allows synchronize_srcu() to return without waiting
	 * if there are no pending read critical sections (which is the
	 * expected case).
	 */
	srcu_idx = srcu_read_lock(&remove_cache_srcu);
	raw_spin_lock_irqsave(&quarantine_lock, flags);

	/*
	 * Update quarantine size in case of hotplug. Allocate a fraction of
	 * the installed memory to quarantine minus per-cpu queue limits.
	 */
	total_size = (totalram_pages() << PAGE_SHIFT) /
		QUARANTINE_FRACTION;
	percpu_quarantines = QUARANTINE_PERCPU_SIZE * num_online_cpus();
	new_quarantine_size = (total_size < percpu_quarantines) ?
		0 : total_size - percpu_quarantines;
	WRITE_ONCE(quarantine_max_size, new_quarantine_size);
	/* Aim at consuming at most 1/2 of slots in quarantine. */
	WRITE_ONCE(quarantine_batch_size, max((size_t)QUARANTINE_PERCPU_SIZE,
		2 * total_size / QUARANTINE_BATCHES));

	if (likely(quarantine_size > quarantine_max_size)) {
		qlist_move_all(&global_quarantine[quarantine_head], &to_free);
		WRITE_ONCE(quarantine_size, quarantine_size - to_free.bytes);
		quarantine_head++;
		if (quarantine_head == QUARANTINE_BATCHES)
			quarantine_head = 0;
	}

	raw_spin_unlock_irqrestore(&quarantine_lock, flags);

	qlist_free_all(&to_free, NULL);
	srcu_read_unlock(&remove_cache_srcu, srcu_idx);
}