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
struct fib_nh_exception {int /*<<< orphan*/  fnhe_rth_output; int /*<<< orphan*/  fnhe_rth_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 struct rtable* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fnhe_flush_routes(struct fib_nh_exception *fnhe)
{
	struct rtable *rt;

	rt = rcu_dereference(fnhe->fnhe_rth_input);
	if (rt) {
		RCU_INIT_POINTER(fnhe->fnhe_rth_input, NULL);
		dst_dev_put(&rt->dst);
		dst_release(&rt->dst);
	}
	rt = rcu_dereference(fnhe->fnhe_rth_output);
	if (rt) {
		RCU_INIT_POINTER(fnhe->fnhe_rth_output, NULL);
		dst_dev_put(&rt->dst);
		dst_release(&rt->dst);
	}
}