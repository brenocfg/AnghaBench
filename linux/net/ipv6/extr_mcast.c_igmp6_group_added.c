#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; } ;
struct ifmcaddr6 {int mca_flags; scalar_t__ mca_sfmode; TYPE_1__* idev; int /*<<< orphan*/  mca_crcount; int /*<<< orphan*/  mca_lock; int /*<<< orphan*/  mca_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  mc_qrv; struct net_device* dev; } ;

/* Variables and functions */
 int IFF_UP ; 
 scalar_t__ IPV6_ADDR_MC_SCOPE (int /*<<< orphan*/ *) ; 
 scalar_t__ IPV6_ADDR_SCOPE_LINKLOCAL ; 
 int MAF_LOADED ; 
 int MAF_NOREPORT ; 
 int MAX_ADDR_LEN ; 
 scalar_t__ MCAST_EXCLUDE ; 
 int /*<<< orphan*/  dev_mc_add (struct net_device*,char*) ; 
 int /*<<< orphan*/  igmp6_join_group (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  mld_ifc_event (TYPE_1__*) ; 
 scalar_t__ mld_in_v1_mode (TYPE_1__*) ; 
 scalar_t__ ndisc_mc_map (int /*<<< orphan*/ *,char*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igmp6_group_added(struct ifmcaddr6 *mc)
{
	struct net_device *dev = mc->idev->dev;
	char buf[MAX_ADDR_LEN];

	if (IPV6_ADDR_MC_SCOPE(&mc->mca_addr) <
	    IPV6_ADDR_SCOPE_LINKLOCAL)
		return;

	spin_lock_bh(&mc->mca_lock);
	if (!(mc->mca_flags&MAF_LOADED)) {
		mc->mca_flags |= MAF_LOADED;
		if (ndisc_mc_map(&mc->mca_addr, buf, dev, 0) == 0)
			dev_mc_add(dev, buf);
	}
	spin_unlock_bh(&mc->mca_lock);

	if (!(dev->flags & IFF_UP) || (mc->mca_flags & MAF_NOREPORT))
		return;

	if (mld_in_v1_mode(mc->idev)) {
		igmp6_join_group(mc);
		return;
	}
	/* else v2 */

	/* Based on RFC3810 6.1, for newly added INCLUDE SSM, we
	 * should not send filter-mode change record as the mode
	 * should be from IN() to IN(A).
	 */
	if (mc->mca_sfmode == MCAST_EXCLUDE)
		mc->mca_crcount = mc->idev->mc_qrv;

	mld_ifc_event(mc->idev);
}