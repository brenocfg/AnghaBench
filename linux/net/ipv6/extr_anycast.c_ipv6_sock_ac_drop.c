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
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ipv6_pinfo {struct ipv6_ac_socklist* ipv6_ac_list; } ;
struct ipv6_ac_socklist {int acl_ifindex; int /*<<< orphan*/  acl_addr; struct ipv6_ac_socklist* acl_next; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOENT ; 
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int /*<<< orphan*/  ipv6_dev_ac_dec (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct ipv6_ac_socklist*,int) ; 
 struct net* sock_net (struct sock*) ; 

int ipv6_sock_ac_drop(struct sock *sk, int ifindex, const struct in6_addr *addr)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct net_device *dev;
	struct ipv6_ac_socklist *pac, *prev_pac;
	struct net *net = sock_net(sk);

	ASSERT_RTNL();

	prev_pac = NULL;
	for (pac = np->ipv6_ac_list; pac; pac = pac->acl_next) {
		if ((ifindex == 0 || pac->acl_ifindex == ifindex) &&
		     ipv6_addr_equal(&pac->acl_addr, addr))
			break;
		prev_pac = pac;
	}
	if (!pac)
		return -ENOENT;
	if (prev_pac)
		prev_pac->acl_next = pac->acl_next;
	else
		np->ipv6_ac_list = pac->acl_next;

	dev = __dev_get_by_index(net, pac->acl_ifindex);
	if (dev)
		ipv6_dev_ac_dec(dev, &pac->acl_addr);

	sock_kfree_s(sk, pac, sizeof(*pac));
	return 0;
}