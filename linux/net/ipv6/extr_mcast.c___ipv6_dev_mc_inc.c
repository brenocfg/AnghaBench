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
struct inet6_dev {int /*<<< orphan*/  lock; struct ifmcaddr6* mc_list; scalar_t__ dead; } ;
struct in6_addr {int dummy; } ;
struct ifmcaddr6 {struct ifmcaddr6* next; int /*<<< orphan*/  mca_addr; int /*<<< orphan*/  mca_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  igmp6_group_added (struct ifmcaddr6*) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  ip6_mc_add_src (struct inet6_dev*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int /*<<< orphan*/  ma_put (struct ifmcaddr6*) ; 
 struct ifmcaddr6* mca_alloc (struct inet6_dev*,struct in6_addr const*,unsigned int) ; 
 int /*<<< orphan*/  mca_get (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  mld_del_delrec (struct inet6_dev*,struct ifmcaddr6*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ipv6_dev_mc_inc(struct net_device *dev,
			     const struct in6_addr *addr, unsigned int mode)
{
	struct ifmcaddr6 *mc;
	struct inet6_dev *idev;

	ASSERT_RTNL();

	/* we need to take a reference on idev */
	idev = in6_dev_get(dev);

	if (!idev)
		return -EINVAL;

	write_lock_bh(&idev->lock);
	if (idev->dead) {
		write_unlock_bh(&idev->lock);
		in6_dev_put(idev);
		return -ENODEV;
	}

	for (mc = idev->mc_list; mc; mc = mc->next) {
		if (ipv6_addr_equal(&mc->mca_addr, addr)) {
			mc->mca_users++;
			write_unlock_bh(&idev->lock);
			ip6_mc_add_src(idev, &mc->mca_addr, mode, 0, NULL, 0);
			in6_dev_put(idev);
			return 0;
		}
	}

	mc = mca_alloc(idev, addr, mode);
	if (!mc) {
		write_unlock_bh(&idev->lock);
		in6_dev_put(idev);
		return -ENOMEM;
	}

	mc->next = idev->mc_list;
	idev->mc_list = mc;

	/* Hold this for the code below before we unlock,
	 * it is already exposed via idev->mc_list.
	 */
	mca_get(mc);
	write_unlock_bh(&idev->lock);

	mld_del_delrec(idev, mc);
	igmp6_group_added(mc);
	ma_put(mc);
	return 0;
}