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
struct kmem_cache {int /*<<< orphan*/  size; } ;
struct kasan_free_meta {int /*<<< orphan*/  quarantine_link; } ;

/* Variables and functions */
 struct qlist_head QLIST_INIT ; 
 int QUARANTINE_BATCHES ; 
 scalar_t__ QUARANTINE_PERCPU_SIZE ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cpu_quarantine ; 
 struct qlist_head* global_quarantine ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  qlist_move_all (struct qlist_head*,struct qlist_head*) ; 
 int /*<<< orphan*/  qlist_put (struct qlist_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quarantine_batch_size ; 
 int quarantine_head ; 
 int /*<<< orphan*/  quarantine_lock ; 
 scalar_t__ quarantine_size ; 
 size_t quarantine_tail ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 struct qlist_head* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void quarantine_put(struct kasan_free_meta *info, struct kmem_cache *cache)
{
	unsigned long flags;
	struct qlist_head *q;
	struct qlist_head temp = QLIST_INIT;

	/*
	 * Note: irq must be disabled until after we move the batch to the
	 * global quarantine. Otherwise quarantine_remove_cache() can miss
	 * some objects belonging to the cache if they are in our local temp
	 * list. quarantine_remove_cache() executes on_each_cpu() at the
	 * beginning which ensures that it either sees the objects in per-cpu
	 * lists or in the global quarantine.
	 */
	local_irq_save(flags);

	q = this_cpu_ptr(&cpu_quarantine);
	qlist_put(q, &info->quarantine_link, cache->size);
	if (unlikely(q->bytes > QUARANTINE_PERCPU_SIZE)) {
		qlist_move_all(q, &temp);

		raw_spin_lock(&quarantine_lock);
		WRITE_ONCE(quarantine_size, quarantine_size + temp.bytes);
		qlist_move_all(&temp, &global_quarantine[quarantine_tail]);
		if (global_quarantine[quarantine_tail].bytes >=
				READ_ONCE(quarantine_batch_size)) {
			int new_tail;

			new_tail = quarantine_tail + 1;
			if (new_tail == QUARANTINE_BATCHES)
				new_tail = 0;
			if (new_tail != quarantine_head)
				quarantine_tail = new_tail;
		}
		raw_spin_unlock(&quarantine_lock);
	}

	local_irq_restore(flags);
}