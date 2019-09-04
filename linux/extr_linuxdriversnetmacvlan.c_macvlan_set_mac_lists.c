#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct macvlan_dev {struct net_device* lowerdev; TYPE_1__* port; int /*<<< orphan*/  mc_filter; } ;
struct TYPE_2__ {int /*<<< orphan*/  mc_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_mc_sync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_uc_sync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  macvlan_compute_filter (int /*<<< orphan*/ ,struct net_device*,struct macvlan_dev*) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void macvlan_set_mac_lists(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	macvlan_compute_filter(vlan->mc_filter, dev, vlan);

	dev_uc_sync(vlan->lowerdev, dev);
	dev_mc_sync(vlan->lowerdev, dev);

	/* This is slightly inaccurate as we're including the subscription
	 * list of vlan->lowerdev too.
	 *
	 * Bug alert: This only works if everyone has the same broadcast
	 * address as lowerdev.  As soon as someone changes theirs this
	 * will break.
	 *
	 * However, this is already broken as when you change your broadcast
	 * address we don't get called.
	 *
	 * The solution is to maintain a list of broadcast addresses like
	 * we do for uc/mc, if you care.
	 */
	macvlan_compute_filter(vlan->port->mc_filter, vlan->lowerdev, NULL);
}