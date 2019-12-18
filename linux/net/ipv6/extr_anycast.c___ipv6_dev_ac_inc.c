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
struct net {int dummy; } ;
struct inet6_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; struct ifacaddr6* ac_list; scalar_t__ dead; } ;
struct in6_addr {int dummy; } ;
struct ifacaddr6 {int /*<<< orphan*/  aca_addr; struct ifacaddr6* aca_next; int /*<<< orphan*/  aca_users; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct fib6_info*) ; 
 int PTR_ERR (struct fib6_info*) ; 
 struct ifacaddr6* aca_alloc (struct fib6_info*,struct in6_addr const*) ; 
 int /*<<< orphan*/  aca_get (struct ifacaddr6*) ; 
 int /*<<< orphan*/  aca_put (struct ifacaddr6*) ; 
 struct fib6_info* addrconf_f6i_alloc (struct net*,struct inet6_dev*,struct in6_addr const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addrconf_join_solict (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 int /*<<< orphan*/  ip6_ins_rt (struct net*,struct fib6_info*) ; 
 int /*<<< orphan*/  ipv6_add_acaddr_hash (struct net*,struct ifacaddr6*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int __ipv6_dev_ac_inc(struct inet6_dev *idev, const struct in6_addr *addr)
{
	struct ifacaddr6 *aca;
	struct fib6_info *f6i;
	struct net *net;
	int err;

	ASSERT_RTNL();

	write_lock_bh(&idev->lock);
	if (idev->dead) {
		err = -ENODEV;
		goto out;
	}

	for (aca = idev->ac_list; aca; aca = aca->aca_next) {
		if (ipv6_addr_equal(&aca->aca_addr, addr)) {
			aca->aca_users++;
			err = 0;
			goto out;
		}
	}

	net = dev_net(idev->dev);
	f6i = addrconf_f6i_alloc(net, idev, addr, true, GFP_ATOMIC);
	if (IS_ERR(f6i)) {
		err = PTR_ERR(f6i);
		goto out;
	}
	aca = aca_alloc(f6i, addr);
	if (!aca) {
		fib6_info_release(f6i);
		err = -ENOMEM;
		goto out;
	}

	aca->aca_next = idev->ac_list;
	idev->ac_list = aca;

	/* Hold this for addrconf_join_solict() below before we unlock,
	 * it is already exposed via idev->ac_list.
	 */
	aca_get(aca);
	write_unlock_bh(&idev->lock);

	ipv6_add_acaddr_hash(net, aca);

	ip6_ins_rt(net, f6i);

	addrconf_join_solict(idev->dev, &aca->aca_addr);

	aca_put(aca);
	return 0;
out:
	write_unlock_bh(&idev->lock);
	return err;
}