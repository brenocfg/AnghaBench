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

/* Variables and functions */
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_dev_ac_dec (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct ipv6_ac_socklist*,int) ; 
 struct net* sock_net (struct sock*) ; 

void ipv6_sock_ac_close(struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct net_device *dev = NULL;
	struct ipv6_ac_socklist *pac;
	struct net *net = sock_net(sk);
	int	prev_index;

	if (!np->ipv6_ac_list)
		return;

	rtnl_lock();
	pac = np->ipv6_ac_list;
	np->ipv6_ac_list = NULL;

	prev_index = 0;
	while (pac) {
		struct ipv6_ac_socklist *next = pac->acl_next;

		if (pac->acl_ifindex != prev_index) {
			dev = __dev_get_by_index(net, pac->acl_ifindex);
			prev_index = pac->acl_ifindex;
		}
		if (dev)
			ipv6_dev_ac_dec(dev, &pac->acl_addr);
		sock_kfree_s(sk, pac, sizeof(*pac));
		pac = next;
	}
	rtnl_unlock();
}