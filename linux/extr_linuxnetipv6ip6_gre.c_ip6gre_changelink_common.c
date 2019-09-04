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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ip_tunnel_encap {int dummy; } ;
struct ip6gre_net {struct net_device* fb_tunnel_dev; } ;
struct ip6_tnl {struct net_device* dev; struct net* net; } ;
struct __ip6_tnl_parm {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 struct ip6_tnl* ERR_PTR (int) ; 
 int ip6_tnl_encap_setup (struct ip6_tnl*,struct ip_tunnel_encap*) ; 
 int /*<<< orphan*/  ip6gre_net_id ; 
 scalar_t__ ip6gre_netlink_encap_parms (struct nlattr**,struct ip_tunnel_encap*) ; 
 int /*<<< orphan*/  ip6gre_netlink_parms (struct nlattr**,struct __ip6_tnl_parm*) ; 
 struct ip6_tnl* ip6gre_tunnel_locate (struct net*,struct __ip6_tnl_parm*,int /*<<< orphan*/ ) ; 
 struct ip6gre_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct ip6_tnl *
ip6gre_changelink_common(struct net_device *dev, struct nlattr *tb[],
			 struct nlattr *data[], struct __ip6_tnl_parm *p_p,
			 struct netlink_ext_ack *extack)
{
	struct ip6_tnl *t, *nt = netdev_priv(dev);
	struct net *net = nt->net;
	struct ip6gre_net *ign = net_generic(net, ip6gre_net_id);
	struct ip_tunnel_encap ipencap;

	if (dev == ign->fb_tunnel_dev)
		return ERR_PTR(-EINVAL);

	if (ip6gre_netlink_encap_parms(data, &ipencap)) {
		int err = ip6_tnl_encap_setup(nt, &ipencap);

		if (err < 0)
			return ERR_PTR(err);
	}

	ip6gre_netlink_parms(data, p_p);

	t = ip6gre_tunnel_locate(net, p_p, 0);

	if (t) {
		if (t->dev != dev)
			return ERR_PTR(-EEXIST);
	} else {
		t = nt;
	}

	return t;
}