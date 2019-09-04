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
 int /*<<< orphan*/  igmp6_group_dropped (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  mld_dad_stop_timer (struct inet6_dev*) ; 
 int /*<<< orphan*/  mld_gq_stop_timer (struct inet6_dev*) ; 
 int /*<<< orphan*/  mld_ifc_stop_timer (struct inet6_dev*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

void ipv6_mc_down(struct inet6_dev *idev)
{
	struct ifmcaddr6 *i;

	/* Withdraw multicast list */

	read_lock_bh(&idev->lock);

	for (i = idev->mc_list; i; i = i->next)
		igmp6_group_dropped(i);

	/* Should stop timer after group drop. or we will
	 * start timer again in mld_ifc_event()
	 */
	mld_ifc_stop_timer(idev);
	mld_gq_stop_timer(idev);
	mld_dad_stop_timer(idev);
	read_unlock_bh(&idev->lock);
}