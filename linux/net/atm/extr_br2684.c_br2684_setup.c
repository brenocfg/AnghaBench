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
struct net_device {int hard_header_len; int /*<<< orphan*/ * netdev_ops; } ;
struct br2684_dev {int /*<<< orphan*/  brvccs; struct net_device* net_dev; } ;
typedef  int /*<<< orphan*/  llc_oui_pid_pad ;

/* Variables and functions */
 struct br2684_dev* BRPRIV (struct net_device*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br2684_netdev_ops ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 

__attribute__((used)) static void br2684_setup(struct net_device *netdev)
{
	struct br2684_dev *brdev = BRPRIV(netdev);

	ether_setup(netdev);
	netdev->hard_header_len += sizeof(llc_oui_pid_pad); /* worst case */
	brdev->net_dev = netdev;

	netdev->netdev_ops = &br2684_netdev_ops;

	INIT_LIST_HEAD(&brdev->brvccs);
}