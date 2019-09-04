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
struct in6_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nh_gw; } ;
struct fib6_info {int fib6_flags; TYPE_1__ fib6_nh; } ;

/* Variables and functions */
 int RTF_RA_ROUTER ; 
 scalar_t__ ipv6_addr_equal (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt6_exceptions_clean_tohost (struct fib6_info*,struct in6_addr*) ; 

__attribute__((used)) static int fib6_clean_tohost(struct fib6_info *rt, void *arg)
{
	struct in6_addr *gateway = (struct in6_addr *)arg;

	if (((rt->fib6_flags & RTF_RA_ROUTER) == RTF_RA_ROUTER) &&
	    ipv6_addr_equal(gateway, &rt->fib6_nh.nh_gw)) {
		return -1;
	}

	/* Further clean up cached routes in exception table.
	 * This is needed because cached route may have a different
	 * gateway than its 'parent' in the case of an ip redirect.
	 */
	rt6_exceptions_clean_tohost(rt, gateway);

	return 0;
}