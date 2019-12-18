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
struct page_counter {unsigned long max; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int EBUSY ; 
 long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long xchg (unsigned long*,unsigned long) ; 

int page_counter_set_max(struct page_counter *counter, unsigned long nr_pages)
{
	for (;;) {
		unsigned long old;
		long usage;

		/*
		 * Update the limit while making sure that it's not
		 * below the concurrently-changing counter value.
		 *
		 * The xchg implies two full memory barriers before
		 * and after, so the read-swap-read is ordered and
		 * ensures coherency with page_counter_try_charge():
		 * that function modifies the count before checking
		 * the limit, so if it sees the old limit, we see the
		 * modified counter and retry.
		 */
		usage = atomic_long_read(&counter->usage);

		if (usage > nr_pages)
			return -EBUSY;

		old = xchg(&counter->max, nr_pages);

		if (atomic_long_read(&counter->usage) <= usage)
			return 0;

		counter->max = old;
		cond_resched();
	}
}