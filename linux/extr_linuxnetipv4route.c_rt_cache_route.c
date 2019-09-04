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
struct rtable {int /*<<< orphan*/  dst; } ;
struct fib_nh {int /*<<< orphan*/  nh_pcpu_rth_output; int /*<<< orphan*/  nh_rth_input; } ;

/* Variables and functions */
 struct rtable* cmpxchg (struct rtable**,struct rtable*,struct rtable*) ; 
 int /*<<< orphan*/  dst_dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 scalar_t__ raw_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ rt_is_input_route (struct rtable*) ; 

__attribute__((used)) static bool rt_cache_route(struct fib_nh *nh, struct rtable *rt)
{
	struct rtable *orig, *prev, **p;
	bool ret = true;

	if (rt_is_input_route(rt)) {
		p = (struct rtable **)&nh->nh_rth_input;
	} else {
		p = (struct rtable **)raw_cpu_ptr(nh->nh_pcpu_rth_output);
	}
	orig = *p;

	/* hold dst before doing cmpxchg() to avoid race condition
	 * on this dst
	 */
	dst_hold(&rt->dst);
	prev = cmpxchg(p, orig, rt);
	if (prev == orig) {
		if (orig) {
			dst_dev_put(&orig->dst);
			dst_release(&orig->dst);
		}
	} else {
		dst_release(&rt->dst);
		ret = false;
	}

	return ret;
}