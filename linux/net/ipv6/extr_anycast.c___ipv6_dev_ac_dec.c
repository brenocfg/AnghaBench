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
struct inet6_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; struct ifacaddr6* ac_list; } ;
struct in6_addr {int dummy; } ;
struct ifacaddr6 {scalar_t__ aca_users; int /*<<< orphan*/  aca_rt; int /*<<< orphan*/  aca_addr; struct ifacaddr6* aca_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOENT ; 
 int /*<<< orphan*/  aca_put (struct ifacaddr6*) ; 
 int /*<<< orphan*/  addrconf_leave_solict (struct inet6_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_del_rt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int /*<<< orphan*/  ipv6_del_acaddr_hash (struct ifacaddr6*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int __ipv6_dev_ac_dec(struct inet6_dev *idev, const struct in6_addr *addr)
{
	struct ifacaddr6 *aca, *prev_aca;

	ASSERT_RTNL();

	write_lock_bh(&idev->lock);
	prev_aca = NULL;
	for (aca = idev->ac_list; aca; aca = aca->aca_next) {
		if (ipv6_addr_equal(&aca->aca_addr, addr))
			break;
		prev_aca = aca;
	}
	if (!aca) {
		write_unlock_bh(&idev->lock);
		return -ENOENT;
	}
	if (--aca->aca_users > 0) {
		write_unlock_bh(&idev->lock);
		return 0;
	}
	if (prev_aca)
		prev_aca->aca_next = aca->aca_next;
	else
		idev->ac_list = aca->aca_next;
	write_unlock_bh(&idev->lock);
	ipv6_del_acaddr_hash(aca);
	addrconf_leave_solict(idev, &aca->aca_addr);

	ip6_del_rt(dev_net(idev->dev), aca->aca_rt);

	aca_put(aca);
	return 0;
}