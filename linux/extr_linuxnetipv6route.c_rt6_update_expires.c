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
struct TYPE_2__ {int /*<<< orphan*/  expires; } ;
struct rt6_info {int rt6i_flags; TYPE_1__ dst; int /*<<< orphan*/  from; } ;
struct fib6_info {int /*<<< orphan*/  expires; } ;

/* Variables and functions */
 int RTF_EXPIRES ; 
 int /*<<< orphan*/  dst_set_expires (TYPE_1__*,int) ; 
 struct fib6_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void rt6_update_expires(struct rt6_info *rt0, int timeout)
{
	if (!(rt0->rt6i_flags & RTF_EXPIRES)) {
		struct fib6_info *from;

		rcu_read_lock();
		from = rcu_dereference(rt0->from);
		if (from)
			rt0->dst.expires = from->expires;
		rcu_read_unlock();
	}

	dst_set_expires(&rt0->dst, timeout);
	rt0->rt6i_flags |= RTF_EXPIRES;
}