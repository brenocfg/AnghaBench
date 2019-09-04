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
struct nlattr {int dummy; } ;
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;
struct net {int dummy; } ;
struct gtp_dev {int dummy; } ;

/* Variables and functions */
 size_t GTPA_LINK ; 
 size_t GTPA_NET_NS_FD ; 
 scalar_t__ IS_ERR (struct net*) ; 
 struct net_device* dev_get_by_index_rcu (struct net*,int /*<<< orphan*/ ) ; 
 struct net* get_net (struct net*) ; 
 struct net* get_net_ns_by_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtp_netdev_ops ; 
 struct gtp_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 

__attribute__((used)) static struct gtp_dev *gtp_find_dev(struct net *src_net, struct nlattr *nla[])
{
	struct gtp_dev *gtp = NULL;
	struct net_device *dev;
	struct net *net;

	/* Examine the link attributes and figure out which network namespace
	 * we are talking about.
	 */
	if (nla[GTPA_NET_NS_FD])
		net = get_net_ns_by_fd(nla_get_u32(nla[GTPA_NET_NS_FD]));
	else
		net = get_net(src_net);

	if (IS_ERR(net))
		return NULL;

	/* Check if there's an existing gtpX device to configure */
	dev = dev_get_by_index_rcu(net, nla_get_u32(nla[GTPA_LINK]));
	if (dev && dev->netdev_ops == &gtp_netdev_ops)
		gtp = netdev_priv(dev);

	put_net(net);
	return gtp;
}