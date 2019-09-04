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
struct ip6gre_net {int dummy; } ;
struct ip6_tnl {int dummy; } ;
struct __ip6_tnl_parm {int dummy; } ;

/* Variables and functions */
 size_t IFLA_MTU ; 
 scalar_t__ IS_ERR (struct ip6_tnl*) ; 
 int PTR_ERR (struct ip6_tnl*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  ip6erspan_set_version (struct nlattr**,struct __ip6_tnl_parm*) ; 
 int /*<<< orphan*/  ip6erspan_tnl_change (struct ip6_tnl*,struct __ip6_tnl_parm*,int) ; 
 int /*<<< orphan*/  ip6erspan_tunnel_link_md (struct ip6gre_net*,struct ip6_tnl*) ; 
 struct ip6_tnl* ip6gre_changelink_common (struct net_device*,struct nlattr**,struct nlattr**,struct __ip6_tnl_parm*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  ip6gre_net_id ; 
 int /*<<< orphan*/  ip6gre_tunnel_link (struct ip6gre_net*,struct ip6_tnl*) ; 
 int /*<<< orphan*/  ip6gre_tunnel_unlink (struct ip6gre_net*,struct ip6_tnl*) ; 
 int /*<<< orphan*/  ip6gre_tunnel_unlink_md (struct ip6gre_net*,struct ip6_tnl*) ; 
 struct ip6gre_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip6erspan_changelink(struct net_device *dev, struct nlattr *tb[],
				struct nlattr *data[],
				struct netlink_ext_ack *extack)
{
	struct ip6gre_net *ign = net_generic(dev_net(dev), ip6gre_net_id);
	struct __ip6_tnl_parm p;
	struct ip6_tnl *t;

	t = ip6gre_changelink_common(dev, tb, data, &p, extack);
	if (IS_ERR(t))
		return PTR_ERR(t);

	ip6erspan_set_version(data, &p);
	ip6gre_tunnel_unlink_md(ign, t);
	ip6gre_tunnel_unlink(ign, t);
	ip6erspan_tnl_change(t, &p, !tb[IFLA_MTU]);
	ip6erspan_tunnel_link_md(ign, t);
	ip6gre_tunnel_link(ign, t);
	return 0;
}