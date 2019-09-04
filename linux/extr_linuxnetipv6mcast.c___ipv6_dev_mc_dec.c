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
struct inet6_dev {int /*<<< orphan*/  lock; struct ifmcaddr6* mc_list; } ;
struct in6_addr {int dummy; } ;
struct ifmcaddr6 {scalar_t__ mca_users; struct ifmcaddr6* next; int /*<<< orphan*/  mca_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOENT ; 
 int /*<<< orphan*/  igmp6_group_dropped (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  ip6_mc_clear_src (struct ifmcaddr6*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int /*<<< orphan*/  ma_put (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int __ipv6_dev_mc_dec(struct inet6_dev *idev, const struct in6_addr *addr)
{
	struct ifmcaddr6 *ma, **map;

	ASSERT_RTNL();

	write_lock_bh(&idev->lock);
	for (map = &idev->mc_list; (ma = *map) != NULL; map = &ma->next) {
		if (ipv6_addr_equal(&ma->mca_addr, addr)) {
			if (--ma->mca_users == 0) {
				*map = ma->next;
				write_unlock_bh(&idev->lock);

				igmp6_group_dropped(ma);
				ip6_mc_clear_src(ma);

				ma_put(ma);
				return 0;
			}
			write_unlock_bh(&idev->lock);
			return 0;
		}
	}
	write_unlock_bh(&idev->lock);

	return -ENOENT;
}