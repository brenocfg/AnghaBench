#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rds_ib_refill_cache {TYPE_1__* percpu; int /*<<< orphan*/  xfer; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  first; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 struct list_head* RDS_IB_RECYCLE_BATCH_COUNT ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct list_head* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,struct list_head*) ; 
 struct list_head* cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  list_splice_entire_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct list_head* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_ib_recv_cache_put(struct list_head *new_item,
				 struct rds_ib_refill_cache *cache)
{
	unsigned long flags;
	struct list_head *old, *chpfirst;

	local_irq_save(flags);

	chpfirst = __this_cpu_read(cache->percpu->first);
	if (!chpfirst)
		INIT_LIST_HEAD(new_item);
	else /* put on front */
		list_add_tail(new_item, chpfirst);

	__this_cpu_write(cache->percpu->first, new_item);
	__this_cpu_inc(cache->percpu->count);

	if (__this_cpu_read(cache->percpu->count) < RDS_IB_RECYCLE_BATCH_COUNT)
		goto end;

	/*
	 * Return our per-cpu first list to the cache's xfer by atomically
	 * grabbing the current xfer list, appending it to our per-cpu list,
	 * and then atomically returning that entire list back to the
	 * cache's xfer list as long as it's still empty.
	 */
	do {
		old = xchg(&cache->xfer, NULL);
		if (old)
			list_splice_entire_tail(old, chpfirst);
		old = cmpxchg(&cache->xfer, NULL, chpfirst);
	} while (old);


	__this_cpu_write(cache->percpu->first, NULL);
	__this_cpu_write(cache->percpu->count, 0);
end:
	local_irq_restore(flags);
}