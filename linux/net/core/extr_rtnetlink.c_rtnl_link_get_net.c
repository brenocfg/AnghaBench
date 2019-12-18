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
 size_t IFLA_NET_NS_FD ; 
 size_t IFLA_NET_NS_PID ; 
 struct net* get_net (struct net*) ; 
 struct net* get_net_ns_by_fd (int /*<<< orphan*/ ) ; 
 struct net* get_net_ns_by_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 

struct net *rtnl_link_get_net(struct net *src_net, struct nlattr *tb[])
{
	struct net *net;
	/* Examine the link attributes and figure out which
	 * network namespace we are talking about.
	 */
	if (tb[IFLA_NET_NS_PID])
		net = get_net_ns_by_pid(nla_get_u32(tb[IFLA_NET_NS_PID]));
	else if (tb[IFLA_NET_NS_FD])
		net = get_net_ns_by_fd(nla_get_u32(tb[IFLA_NET_NS_FD]));
	else
		net = get_net(src_net);
	return net;
}