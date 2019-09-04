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
struct page_counter {unsigned long min; unsigned long low; TYPE_1__* parent; int /*<<< orphan*/  low_usage; int /*<<< orphan*/  min_usage; } ;
struct TYPE_2__ {int /*<<< orphan*/  children_low_usage; int /*<<< orphan*/  children_min_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_add (long,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 unsigned long atomic_long_xchg (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void propagate_protected_usage(struct page_counter *c,
				      unsigned long usage)
{
	unsigned long protected, old_protected;
	long delta;

	if (!c->parent)
		return;

	if (c->min || atomic_long_read(&c->min_usage)) {
		if (usage <= c->min)
			protected = usage;
		else
			protected = 0;

		old_protected = atomic_long_xchg(&c->min_usage, protected);
		delta = protected - old_protected;
		if (delta)
			atomic_long_add(delta, &c->parent->children_min_usage);
	}

	if (c->low || atomic_long_read(&c->low_usage)) {
		if (usage <= c->low)
			protected = usage;
		else
			protected = 0;

		old_protected = atomic_long_xchg(&c->low_usage, protected);
		delta = protected - old_protected;
		if (delta)
			atomic_long_add(delta, &c->parent->children_low_usage);
	}
}