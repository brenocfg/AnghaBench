#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long expires; } ;
struct ifmcaddr6 {int mca_flags; int /*<<< orphan*/  mca_lock; int /*<<< orphan*/  mca_refcnt; TYPE_2__ mca_timer; TYPE_1__* idev; int /*<<< orphan*/  mca_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_MGM_REPORT ; 
 int MAF_LAST_REPORTER ; 
 int MAF_NOREPORT ; 
 int MAF_TIMER_RUNNING ; 
 scalar_t__ del_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  igmp6_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_2__*,unsigned long) ; 
 unsigned long prandom_u32 () ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned long unsolicited_report_interval (TYPE_1__*) ; 

__attribute__((used)) static void igmp6_join_group(struct ifmcaddr6 *ma)
{
	unsigned long delay;

	if (ma->mca_flags & MAF_NOREPORT)
		return;

	igmp6_send(&ma->mca_addr, ma->idev->dev, ICMPV6_MGM_REPORT);

	delay = prandom_u32() % unsolicited_report_interval(ma->idev);

	spin_lock_bh(&ma->mca_lock);
	if (del_timer(&ma->mca_timer)) {
		refcount_dec(&ma->mca_refcnt);
		delay = ma->mca_timer.expires - jiffies;
	}

	if (!mod_timer(&ma->mca_timer, jiffies + delay))
		refcount_inc(&ma->mca_refcnt);
	ma->mca_flags |= MAF_TIMER_RUNNING | MAF_LAST_REPORTER;
	spin_unlock_bh(&ma->mca_lock);
}