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
struct net {int dummy; } ;
struct inet6_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool ipv6_use_optimistic_addr(struct net *net,
				     struct inet6_dev *idev)
{
#ifdef CONFIG_IPV6_OPTIMISTIC_DAD
	if (!idev)
		return false;
	if (!net->ipv6.devconf_all->optimistic_dad && !idev->cnf.optimistic_dad)
		return false;
	if (!net->ipv6.devconf_all->use_optimistic && !idev->cnf.use_optimistic)
		return false;

	return true;
#else
	return false;
#endif
}