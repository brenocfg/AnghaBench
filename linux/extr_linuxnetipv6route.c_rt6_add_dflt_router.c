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
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct fib6_table {int /*<<< orphan*/  flags; } ;
struct fib6_info {int dummy; } ;
struct TYPE_2__ {struct net* nl_net; int /*<<< orphan*/ * nlh; int /*<<< orphan*/  portid; } ;
struct fib6_config {int fc_flags; int /*<<< orphan*/  fc_table; struct in6_addr fc_gateway; TYPE_1__ fc_nlinfo; int /*<<< orphan*/  fc_type; int /*<<< orphan*/  fc_protocol; int /*<<< orphan*/  fc_ifindex; int /*<<< orphan*/  fc_metric; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IP6_RT_PRIO_USER ; 
 int /*<<< orphan*/  RT6_TABLE_DFLT ; 
 int /*<<< orphan*/  RT6_TABLE_HAS_DFLT_ROUTER ; 
 int RTF_ADDRCONF ; 
 int RTF_DEFAULT ; 
 int RTF_EXPIRES ; 
 int RTF_GATEWAY ; 
 int RTF_PREF (unsigned int) ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RTN_UNICAST ; 
 int /*<<< orphan*/  RTPROT_RA ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct fib6_table* fib6_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_route_add (struct fib6_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3mdev_fib_table (struct net_device*) ; 
 struct fib6_info* rt6_get_dflt_router (struct net*,struct in6_addr const*,struct net_device*) ; 

struct fib6_info *rt6_add_dflt_router(struct net *net,
				     const struct in6_addr *gwaddr,
				     struct net_device *dev,
				     unsigned int pref)
{
	struct fib6_config cfg = {
		.fc_table	= l3mdev_fib_table(dev) ? : RT6_TABLE_DFLT,
		.fc_metric	= IP6_RT_PRIO_USER,
		.fc_ifindex	= dev->ifindex,
		.fc_flags	= RTF_GATEWAY | RTF_ADDRCONF | RTF_DEFAULT |
				  RTF_UP | RTF_EXPIRES | RTF_PREF(pref),
		.fc_protocol = RTPROT_RA,
		.fc_type = RTN_UNICAST,
		.fc_nlinfo.portid = 0,
		.fc_nlinfo.nlh = NULL,
		.fc_nlinfo.nl_net = net,
	};

	cfg.fc_gateway = *gwaddr;

	if (!ip6_route_add(&cfg, GFP_ATOMIC, NULL)) {
		struct fib6_table *table;

		table = fib6_get_table(dev_net(dev), cfg.fc_table);
		if (table)
			table->flags |= RT6_TABLE_HAS_DFLT_ROUTER;
	}

	return rt6_get_dflt_router(net, gwaddr, dev);
}