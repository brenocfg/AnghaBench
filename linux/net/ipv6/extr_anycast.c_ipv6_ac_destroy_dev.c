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
struct inet6_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; struct ifacaddr6* ac_list; } ;
struct ifacaddr6 {int /*<<< orphan*/  aca_rt; int /*<<< orphan*/  aca_addr; struct ifacaddr6* aca_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  aca_put (struct ifacaddr6*) ; 
 int /*<<< orphan*/  addrconf_leave_solict (struct inet6_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_del_rt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_del_acaddr_hash (struct ifacaddr6*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void ipv6_ac_destroy_dev(struct inet6_dev *idev)
{
	struct ifacaddr6 *aca;

	write_lock_bh(&idev->lock);
	while ((aca = idev->ac_list) != NULL) {
		idev->ac_list = aca->aca_next;
		write_unlock_bh(&idev->lock);

		ipv6_del_acaddr_hash(aca);

		addrconf_leave_solict(idev, &aca->aca_addr);

		ip6_del_rt(dev_net(idev->dev), aca->aca_rt);

		aca_put(aca);

		write_lock_bh(&idev->lock);
	}
	write_unlock_bh(&idev->lock);
}