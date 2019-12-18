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
struct net_device {int dummy; } ;
struct inet6_ifaddr {int /*<<< orphan*/  addr_lst; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  addrconf_hash_lock ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int inet6_addr_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * inet6_addr_lst ; 
 scalar_t__ ipv6_chk_same_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipv6_add_addr_hash(struct net_device *dev, struct inet6_ifaddr *ifa)
{
	unsigned int hash = inet6_addr_hash(dev_net(dev), &ifa->addr);
	int err = 0;

	spin_lock(&addrconf_hash_lock);

	/* Ignore adding duplicate addresses on an interface */
	if (ipv6_chk_same_addr(dev_net(dev), &ifa->addr, dev, hash)) {
		netdev_dbg(dev, "ipv6_add_addr: already assigned\n");
		err = -EEXIST;
	} else {
		hlist_add_head_rcu(&ifa->addr_lst, &inet6_addr_lst[hash]);
	}

	spin_unlock(&addrconf_hash_lock);

	return err;
}