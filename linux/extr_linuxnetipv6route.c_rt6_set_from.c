#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  _metrics; } ;
struct rt6_info {TYPE_1__ dst; int /*<<< orphan*/  from; int /*<<< orphan*/  rt6i_flags; } ;
struct fib6_info {TYPE_2__* fib6_metrics; } ;
struct TYPE_4__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  metrics; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_METRICS_REFCOUNTED ; 
 int /*<<< orphan*/  RTF_EXPIRES ; 
 TYPE_2__ dst_default_metrics ; 
 int /*<<< orphan*/  dst_init_metrics (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct fib6_info*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt6_set_from(struct rt6_info *rt, struct fib6_info *from)
{
	rt->rt6i_flags &= ~RTF_EXPIRES;
	rcu_assign_pointer(rt->from, from);
	dst_init_metrics(&rt->dst, from->fib6_metrics->metrics, true);
	if (from->fib6_metrics != &dst_default_metrics) {
		rt->dst._metrics |= DST_METRICS_REFCOUNTED;
		refcount_inc(&from->fib6_metrics->refcnt);
	}
}