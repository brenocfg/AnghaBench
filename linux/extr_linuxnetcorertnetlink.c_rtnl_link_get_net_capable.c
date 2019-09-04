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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 struct net* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct net*) ; 
 int /*<<< orphan*/  netlink_ns_capable (struct sk_buff const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 struct net* rtnl_link_get_net_by_nlattr (struct net*,struct nlattr**) ; 

__attribute__((used)) static struct net *rtnl_link_get_net_capable(const struct sk_buff *skb,
					     struct net *src_net,
					     struct nlattr *tb[], int cap)
{
	struct net *net;

	net = rtnl_link_get_net_by_nlattr(src_net, tb);
	if (IS_ERR(net))
		return net;

	if (!netlink_ns_capable(skb, net->user_ns, cap)) {
		put_net(net);
		return ERR_PTR(-EPERM);
	}

	return net;
}