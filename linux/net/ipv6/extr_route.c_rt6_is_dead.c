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
struct fib6_info {TYPE_1__* fib6_nh; } ;
struct TYPE_2__ {int fib_nh_flags; int /*<<< orphan*/  fib_nh_dev; } ;

/* Variables and functions */
 int RTNH_F_DEAD ; 
 int RTNH_F_LINKDOWN ; 
 scalar_t__ ip6_ignore_linkdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rt6_is_dead(const struct fib6_info *rt)
{
	if (rt->fib6_nh->fib_nh_flags & RTNH_F_DEAD ||
	    (rt->fib6_nh->fib_nh_flags & RTNH_F_LINKDOWN &&
	     ip6_ignore_linkdown(rt->fib6_nh->fib_nh_dev)))
		return true;

	return false;
}