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
struct rt6_info {int /*<<< orphan*/  dst; int /*<<< orphan*/  from; int /*<<< orphan*/  rt6i_flags; } ;
struct fib6_info {int /*<<< orphan*/  fib6_metrics; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTF_EXPIRES ; 
 int /*<<< orphan*/  ip_dst_init_metrics (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct fib6_info*) ; 

__attribute__((used)) static void rt6_set_from(struct rt6_info *rt, struct fib6_info *from)
{
	rt->rt6i_flags &= ~RTF_EXPIRES;
	rcu_assign_pointer(rt->from, from);
	ip_dst_init_metrics(&rt->dst, from->fib6_metrics);
}