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
struct TYPE_2__ {scalar_t__ obsolete; int /*<<< orphan*/  expires; } ;
struct rt6_info {int rt6i_flags; TYPE_1__ dst; int /*<<< orphan*/  from; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ DST_OBSOLETE_FORCE_CHK ; 
 int RTF_EXPIRES ; 
 scalar_t__ fib6_check_expired (struct fib6_info*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct fib6_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rt6_check_expired(const struct rt6_info *rt)
{
	struct fib6_info *from;

	from = rcu_dereference(rt->from);

	if (rt->rt6i_flags & RTF_EXPIRES) {
		if (time_after(jiffies, rt->dst.expires))
			return true;
	} else if (from) {
		return rt->dst.obsolete != DST_OBSOLETE_FORCE_CHK ||
			fib6_check_expired(from);
	}
	return false;
}