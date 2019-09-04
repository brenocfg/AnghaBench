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
struct page_counter {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 long atomic_long_sub_return (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  propagate_protected_usage (struct page_counter*,long) ; 

void page_counter_cancel(struct page_counter *counter, unsigned long nr_pages)
{
	long new;

	new = atomic_long_sub_return(nr_pages, &counter->usage);
	propagate_protected_usage(counter, new);
	/* More uncharges than charges? */
	WARN_ON_ONCE(new < 0);
}