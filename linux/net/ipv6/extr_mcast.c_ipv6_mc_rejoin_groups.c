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
struct ifmcaddr6 {struct ifmcaddr6* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  igmp6_join_group (struct ifmcaddr6*) ; 
 scalar_t__ mld_in_v1_mode (struct inet6_dev*) ; 
 int /*<<< orphan*/  mld_send_report (struct inet6_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipv6_mc_rejoin_groups(struct inet6_dev *idev)
{
	struct ifmcaddr6 *pmc;

	ASSERT_RTNL();

	if (mld_in_v1_mode(idev)) {
		read_lock_bh(&idev->lock);
		for (pmc = idev->mc_list; pmc; pmc = pmc->next)
			igmp6_join_group(pmc);
		read_unlock_bh(&idev->lock);
	} else
		mld_send_report(idev, NULL);
}