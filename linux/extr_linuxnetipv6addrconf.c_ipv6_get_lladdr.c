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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct inet6_dev {int /*<<< orphan*/  lock; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int __ipv6_get_lladdr (struct inet6_dev*,struct in6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

int ipv6_get_lladdr(struct net_device *dev, struct in6_addr *addr,
		    u32 banned_flags)
{
	struct inet6_dev *idev;
	int err = -EADDRNOTAVAIL;

	rcu_read_lock();
	idev = __in6_dev_get(dev);
	if (idev) {
		read_lock_bh(&idev->lock);
		err = __ipv6_get_lladdr(idev, addr, banned_flags);
		read_unlock_bh(&idev->lock);
	}
	rcu_read_unlock();
	return err;
}