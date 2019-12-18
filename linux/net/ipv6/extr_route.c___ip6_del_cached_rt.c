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
struct TYPE_4__ {TYPE_1__* dev; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_gateway; TYPE_2__ dst; } ;
struct fib6_config {scalar_t__ fc_ifindex; int fc_flags; int /*<<< orphan*/  fc_gateway; } ;
struct TYPE_3__ {scalar_t__ ifindex; } ;

/* Variables and functions */
 int ESRCH ; 
 int RTF_GATEWAY ; 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rt6_remove_exception_rt (struct rt6_info*) ; 

__attribute__((used)) static int __ip6_del_cached_rt(struct rt6_info *rt, struct fib6_config *cfg)
{
	int rc = -ESRCH;

	if (cfg->fc_ifindex && rt->dst.dev->ifindex != cfg->fc_ifindex)
		goto out;

	if (cfg->fc_flags & RTF_GATEWAY &&
	    !ipv6_addr_equal(&cfg->fc_gateway, &rt->rt6i_gateway))
		goto out;

	rc = rt6_remove_exception_rt(rt);
out:
	return rc;
}