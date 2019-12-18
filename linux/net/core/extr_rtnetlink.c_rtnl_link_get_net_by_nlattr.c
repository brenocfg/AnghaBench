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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct net* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t IFLA_NET_NS_FD ; 
 size_t IFLA_NET_NS_PID ; 
 size_t IFLA_TARGET_NETNSID ; 
 struct net* get_net (struct net*) ; 
 struct net* get_net_ns_by_id (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 struct net* rtnl_link_get_net (struct net*,struct nlattr**) ; 

__attribute__((used)) static struct net *rtnl_link_get_net_by_nlattr(struct net *src_net,
					       struct nlattr *tb[])
{
	struct net *net;

	if (tb[IFLA_NET_NS_PID] || tb[IFLA_NET_NS_FD])
		return rtnl_link_get_net(src_net, tb);

	if (!tb[IFLA_TARGET_NETNSID])
		return get_net(src_net);

	net = get_net_ns_by_id(src_net, nla_get_u32(tb[IFLA_TARGET_NETNSID]));
	if (!net)
		return ERR_PTR(-EINVAL);

	return net;
}