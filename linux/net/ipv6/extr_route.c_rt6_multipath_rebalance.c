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
struct fib6_info {scalar_t__ should_flush; int /*<<< orphan*/  fib6_nsiblings; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct fib6_info* rt6_multipath_first_sibling (struct fib6_info*) ; 
 int rt6_multipath_total_weight (struct fib6_info*) ; 
 int /*<<< orphan*/  rt6_multipath_upper_bound_set (struct fib6_info*,int) ; 

void rt6_multipath_rebalance(struct fib6_info *rt)
{
	struct fib6_info *first;
	int total;

	/* In case the entire multipath route was marked for flushing,
	 * then there is no need to rebalance upon the removal of every
	 * sibling route.
	 */
	if (!rt->fib6_nsiblings || rt->should_flush)
		return;

	/* During lookup routes are evaluated in order, so we need to
	 * make sure upper bounds are assigned from the first sibling
	 * onwards.
	 */
	first = rt6_multipath_first_sibling(rt);
	if (WARN_ON_ONCE(!first))
		return;

	total = rt6_multipath_total_weight(first);
	rt6_multipath_upper_bound_set(first, total);
}