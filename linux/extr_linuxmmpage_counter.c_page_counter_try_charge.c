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
struct page_counter {long max; long watermark; struct page_counter* parent; int /*<<< orphan*/  failcnt; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 long atomic_long_add_return (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_sub (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_counter_cancel (struct page_counter*,unsigned long) ; 
 int /*<<< orphan*/  propagate_protected_usage (struct page_counter*,long) ; 

bool page_counter_try_charge(struct page_counter *counter,
			     unsigned long nr_pages,
			     struct page_counter **fail)
{
	struct page_counter *c;

	for (c = counter; c; c = c->parent) {
		long new;
		/*
		 * Charge speculatively to avoid an expensive CAS.  If
		 * a bigger charge fails, it might falsely lock out a
		 * racing smaller charge and send it into reclaim
		 * early, but the error is limited to the difference
		 * between the two sizes, which is less than 2M/4M in
		 * case of a THP locking out a regular page charge.
		 *
		 * The atomic_long_add_return() implies a full memory
		 * barrier between incrementing the count and reading
		 * the limit.  When racing with page_counter_limit(),
		 * we either see the new limit or the setter sees the
		 * counter has changed and retries.
		 */
		new = atomic_long_add_return(nr_pages, &c->usage);
		if (new > c->max) {
			atomic_long_sub(nr_pages, &c->usage);
			propagate_protected_usage(counter, new);
			/*
			 * This is racy, but we can live with some
			 * inaccuracy in the failcnt.
			 */
			c->failcnt++;
			*fail = c;
			goto failed;
		}
		propagate_protected_usage(counter, new);
		/*
		 * Just like with failcnt, we can live with some
		 * inaccuracy in the watermark.
		 */
		if (new > c->watermark)
			c->watermark = new;
	}
	return true;

failed:
	for (c = counter; c != *fail; c = c->parent)
		page_counter_cancel(c, nr_pages);

	return false;
}