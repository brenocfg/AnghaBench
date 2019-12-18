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
struct TYPE_3__ {int /*<<< orphan*/  icmpv6_ratemask; } ;
struct TYPE_4__ {TYPE_1__ sysctl; } ;
struct net {TYPE_2__ ipv6; } ;

/* Variables and functions */
 int ICMPV6_MSG_MAX ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool icmpv6_mask_allow(struct net *net, int type)
{
	if (type > ICMPV6_MSG_MAX)
		return true;

	/* Limit if icmp type is set in ratemask. */
	if (!test_bit(type, net->ipv6.sysctl.icmpv6_ratemask))
		return true;

	return false;
}