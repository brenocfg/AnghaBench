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
struct napi_struct {unsigned long state; int /*<<< orphan*/  poll_list; int /*<<< orphan*/  timer; TYPE_1__* dev; scalar_t__ gro_bitmask; } ;
struct TYPE_2__ {unsigned long gro_flush_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 unsigned long NAPIF_STATE_IN_BUSY_POLL ; 
 unsigned long NAPIF_STATE_MISSED ; 
 unsigned long NAPIF_STATE_NPSVC ; 
 unsigned long NAPIF_STATE_SCHED ; 
 unsigned long READ_ONCE (unsigned long) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __napi_schedule (struct napi_struct*) ; 
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gro_normal_list (struct napi_struct*) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  napi_gro_flush (struct napi_struct*,int) ; 
 int /*<<< orphan*/  ns_to_ktime (unsigned long) ; 
 scalar_t__ unlikely (unsigned long) ; 

bool napi_complete_done(struct napi_struct *n, int work_done)
{
	unsigned long flags, val, new;

	/*
	 * 1) Don't let napi dequeue from the cpu poll list
	 *    just in case its running on a different cpu.
	 * 2) If we are busy polling, do nothing here, we have
	 *    the guarantee we will be called later.
	 */
	if (unlikely(n->state & (NAPIF_STATE_NPSVC |
				 NAPIF_STATE_IN_BUSY_POLL)))
		return false;

	gro_normal_list(n);

	if (n->gro_bitmask) {
		unsigned long timeout = 0;

		if (work_done)
			timeout = n->dev->gro_flush_timeout;

		/* When the NAPI instance uses a timeout and keeps postponing
		 * it, we need to bound somehow the time packets are kept in
		 * the GRO layer
		 */
		napi_gro_flush(n, !!timeout);
		if (timeout)
			hrtimer_start(&n->timer, ns_to_ktime(timeout),
				      HRTIMER_MODE_REL_PINNED);
	}
	if (unlikely(!list_empty(&n->poll_list))) {
		/* If n->poll_list is not empty, we need to mask irqs */
		local_irq_save(flags);
		list_del_init(&n->poll_list);
		local_irq_restore(flags);
	}

	do {
		val = READ_ONCE(n->state);

		WARN_ON_ONCE(!(val & NAPIF_STATE_SCHED));

		new = val & ~(NAPIF_STATE_MISSED | NAPIF_STATE_SCHED);

		/* If STATE_MISSED was set, leave STATE_SCHED set,
		 * because we will call napi->poll() one more time.
		 * This C code was suggested by Alexander Duyck to help gcc.
		 */
		new |= (val & NAPIF_STATE_MISSED) / NAPIF_STATE_MISSED *
						    NAPIF_STATE_SCHED;
	} while (cmpxchg(&n->state, val, new) != val);

	if (unlikely(val & NAPIF_STATE_MISSED)) {
		__napi_schedule(n);
		return false;
	}

	return true;
}