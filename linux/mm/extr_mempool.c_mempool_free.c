#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ curr_nr; scalar_t__ min_nr; int /*<<< orphan*/  pool_data; int /*<<< orphan*/  (* free ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; } ;
typedef  TYPE_1__ mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_element (TYPE_1__*,void*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void mempool_free(void *element, mempool_t *pool)
{
	unsigned long flags;

	if (unlikely(element == NULL))
		return;

	/*
	 * Paired with the wmb in mempool_alloc().  The preceding read is
	 * for @element and the following @pool->curr_nr.  This ensures
	 * that the visible value of @pool->curr_nr is from after the
	 * allocation of @element.  This is necessary for fringe cases
	 * where @element was passed to this task without going through
	 * barriers.
	 *
	 * For example, assume @p is %NULL at the beginning and one task
	 * performs "p = mempool_alloc(...);" while another task is doing
	 * "while (!p) cpu_relax(); mempool_free(p, ...);".  This function
	 * may end up using curr_nr value which is from before allocation
	 * of @p without the following rmb.
	 */
	smp_rmb();

	/*
	 * For correctness, we need a test which is guaranteed to trigger
	 * if curr_nr + #allocated == min_nr.  Testing curr_nr < min_nr
	 * without locking achieves that and refilling as soon as possible
	 * is desirable.
	 *
	 * Because curr_nr visible here is always a value after the
	 * allocation of @element, any task which decremented curr_nr below
	 * min_nr is guaranteed to see curr_nr < min_nr unless curr_nr gets
	 * incremented to min_nr afterwards.  If curr_nr gets incremented
	 * to min_nr after the allocation of @element, the elements
	 * allocated after that are subject to the same guarantee.
	 *
	 * Waiters happen iff curr_nr is 0 and the above guarantee also
	 * ensures that there will be frees which return elements to the
	 * pool waking up the waiters.
	 */
	if (unlikely(pool->curr_nr < pool->min_nr)) {
		spin_lock_irqsave(&pool->lock, flags);
		if (likely(pool->curr_nr < pool->min_nr)) {
			add_element(pool, element);
			spin_unlock_irqrestore(&pool->lock, flags);
			wake_up(&pool->wait);
			return;
		}
		spin_unlock_irqrestore(&pool->lock, flags);
	}
	pool->free(element, pool->pool_data);
}