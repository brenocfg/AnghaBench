#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/  type; } ;
struct net {int dummy; } ;
struct ip6gre_net {int /*<<< orphan*/  collect_md_tun_erspan; } ;
struct TYPE_4__ {scalar_t__ collect_md; } ;
struct ip6_tnl {TYPE_1__ parms; } ;

/* Variables and functions */
 int EEXIST ; 
 size_t IFLA_MTU ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  ip6erspan_set_version (struct nlattr**,TYPE_1__*) ; 
 int /*<<< orphan*/  ip6erspan_tnl_link_config (struct ip6_tnl*,int) ; 
 int /*<<< orphan*/  ip6erspan_tunnel_link_md (struct ip6gre_net*,struct ip6_tnl*) ; 
 int /*<<< orphan*/  ip6gre_net_id ; 
 int /*<<< orphan*/  ip6gre_netlink_parms (struct nlattr**,TYPE_1__*) ; 
 int ip6gre_newlink_common (struct net*,struct net_device*,struct nlattr**,struct nlattr**,struct netlink_ext_ack*) ; 
 scalar_t__ ip6gre_tunnel_find (struct net*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6gre_tunnel_link (struct ip6gre_net*,struct ip6_tnl*) ; 
 struct ip6gre_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 
 scalar_t__ rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip6erspan_newlink(struct net *src_net, struct net_device *dev,
			     struct nlattr *tb[], struct nlattr *data[],
			     struct netlink_ext_ack *extack)
{
	struct ip6_tnl *nt = netdev_priv(dev);
	struct net *net = dev_net(dev);
	struct ip6gre_net *ign;
	int err;

	ip6gre_netlink_parms(data, &nt->parms);
	ip6erspan_set_version(data, &nt->parms);
	ign = net_generic(net, ip6gre_net_id);

	if (nt->parms.collect_md) {
		if (rtnl_dereference(ign->collect_md_tun_erspan))
			return -EEXIST;
	} else {
		if (ip6gre_tunnel_find(net, &nt->parms, dev->type))
			return -EEXIST;
	}

	err = ip6gre_newlink_common(src_net, dev, tb, data, extack);
	if (!err) {
		ip6erspan_tnl_link_config(nt, !tb[IFLA_MTU]);
		ip6erspan_tunnel_link_md(ign, nt);
		ip6gre_tunnel_link(net_generic(net, ip6gre_net_id), nt);
	}
	return err;
}