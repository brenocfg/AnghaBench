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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct mpls_route {int dummy; } ;
struct mpls_nh {int nh_via_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
#define  NEIGH_ARP_TABLE 130 
#define  NEIGH_LINK_TABLE 129 
#define  NEIGH_ND_TABLE 128 
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net_device* inet6_fib_lookup_dev (struct net*,int /*<<< orphan*/ ) ; 
 struct net_device* inet_fib_lookup_dev (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpls_nh_via (struct mpls_route*,struct mpls_nh*) ; 

__attribute__((used)) static struct net_device *find_outdev(struct net *net,
				      struct mpls_route *rt,
				      struct mpls_nh *nh, int oif)
{
	struct net_device *dev = NULL;

	if (!oif) {
		switch (nh->nh_via_table) {
		case NEIGH_ARP_TABLE:
			dev = inet_fib_lookup_dev(net, mpls_nh_via(rt, nh));
			break;
		case NEIGH_ND_TABLE:
			dev = inet6_fib_lookup_dev(net, mpls_nh_via(rt, nh));
			break;
		case NEIGH_LINK_TABLE:
			break;
		}
	} else {
		dev = dev_get_by_index(net, oif);
	}

	if (!dev)
		return ERR_PTR(-ENODEV);

	if (IS_ERR(dev))
		return dev;

	/* The caller is holding rtnl anyways, so release the dev reference */
	dev_put(dev);

	return dev;
}