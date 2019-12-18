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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int flags; } ;
struct in_ifaddr {scalar_t__ ifa_address; scalar_t__ ifa_mask; int ifa_flags; scalar_t__ ifa_local; int ifa_prefixlen; int /*<<< orphan*/  ifa_rt_priority; struct in_device* ifa_dev; } ;
struct in_device {struct net_device* dev; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int IFA_F_NOPREFIXROUTE ; 
 int IFA_F_SECONDARY ; 
 int IFF_LOOPBACK ; 
 int IFF_UP ; 
 int /*<<< orphan*/  RTM_DELROUTE ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 int /*<<< orphan*/  RTN_LOCAL ; 
 int /*<<< orphan*/  RTN_UNICAST ; 
 int /*<<< orphan*/  fib_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,struct in_ifaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_zeronet (scalar_t__) ; 

void fib_modify_prefix_metric(struct in_ifaddr *ifa, u32 new_metric)
{
	__be32 prefix = ifa->ifa_address & ifa->ifa_mask;
	struct in_device *in_dev = ifa->ifa_dev;
	struct net_device *dev = in_dev->dev;

	if (!(dev->flags & IFF_UP) ||
	    ifa->ifa_flags & (IFA_F_SECONDARY | IFA_F_NOPREFIXROUTE) ||
	    ipv4_is_zeronet(prefix) ||
	    (prefix == ifa->ifa_local && ifa->ifa_prefixlen == 32))
		return;

	/* add the new */
	fib_magic(RTM_NEWROUTE,
		  dev->flags & IFF_LOOPBACK ? RTN_LOCAL : RTN_UNICAST,
		  prefix, ifa->ifa_prefixlen, ifa, new_metric);

	/* delete the old */
	fib_magic(RTM_DELROUTE,
		  dev->flags & IFF_LOOPBACK ? RTN_LOCAL : RTN_UNICAST,
		  prefix, ifa->ifa_prefixlen, ifa, ifa->ifa_rt_priority);
}