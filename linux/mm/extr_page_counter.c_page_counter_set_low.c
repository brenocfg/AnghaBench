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
struct page_counter {unsigned long low; int /*<<< orphan*/  usage; struct page_counter* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  propagate_protected_usage (struct page_counter*,int /*<<< orphan*/ ) ; 

void page_counter_set_low(struct page_counter *counter, unsigned long nr_pages)
{
	struct page_counter *c;

	counter->low = nr_pages;

	for (c = counter; c; c = c->parent)
		propagate_protected_usage(c, atomic_long_read(&c->usage));
}