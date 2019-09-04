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
struct phy_device {int speed; int duplex; int link; } ;
struct net_local {int last_link; struct phy_device* phy_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void xemaclite_adjust_link(struct net_device *ndev)
{
	struct net_local *lp = netdev_priv(ndev);
	struct phy_device *phy = lp->phy_dev;
	int link_state;

	/* hash together the state values to decide if something has changed */
	link_state = phy->speed | (phy->duplex << 1) | phy->link;

	if (lp->last_link != link_state) {
		lp->last_link = link_state;
		phy_print_status(phy);
	}
}