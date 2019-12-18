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
struct seg6_pernet_data {int /*<<< orphan*/  tun_src; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_PREFER_SRC_PUBLIC ; 
 int /*<<< orphan*/  ipv6_addr_any (struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_dev_get_saddr (struct net*,struct net_device*,struct in6_addr*,int /*<<< orphan*/ ,struct in6_addr*) ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,struct in6_addr*,int) ; 
 struct in6_addr* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct seg6_pernet_data* seg6_pernet (struct net*) ; 

__attribute__((used)) static void set_tun_src(struct net *net, struct net_device *dev,
			struct in6_addr *daddr, struct in6_addr *saddr)
{
	struct seg6_pernet_data *sdata = seg6_pernet(net);
	struct in6_addr *tun_src;

	rcu_read_lock();

	tun_src = rcu_dereference(sdata->tun_src);

	if (!ipv6_addr_any(tun_src)) {
		memcpy(saddr, tun_src, sizeof(struct in6_addr));
	} else {
		ipv6_dev_get_saddr(net, dev, daddr, IPV6_PREFER_SRC_PUBLIC,
				   saddr);
	}

	rcu_read_unlock();
}