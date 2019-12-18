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
struct page_counter {struct page_counter* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_counter_cancel (struct page_counter*,unsigned long) ; 

void page_counter_uncharge(struct page_counter *counter, unsigned long nr_pages)
{
	struct page_counter *c;

	for (c = counter; c; c = c->parent)
		page_counter_cancel(c, nr_pages);
}