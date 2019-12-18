#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* devconf_all; } ;
struct net {TYPE_2__ ipv6; } ;
struct TYPE_6__ {int /*<<< orphan*/  optimistic_dad; } ;
struct inet6_dev {TYPE_3__ cnf; } ;
struct TYPE_4__ {int /*<<< orphan*/  optimistic_dad; } ;

/* Variables and functions */

__attribute__((used)) static bool ipv6_allow_optimistic_dad(struct net *net,
				      struct inet6_dev *idev)
{
#ifdef CONFIG_IPV6_OPTIMISTIC_DAD
	if (!idev)
		return false;
	if (!net->ipv6.devconf_all->optimistic_dad && !idev->cnf.optimistic_dad)
		return false;

	return true;
#else
	return false;
#endif
}