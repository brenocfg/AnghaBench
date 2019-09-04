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
struct dlci_local {int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 int dev_set_mtu (int /*<<< orphan*/ ,int) ; 
 struct dlci_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dlci_change_mtu(struct net_device *dev, int new_mtu)
{
	struct dlci_local *dlp = netdev_priv(dev);

	return dev_set_mtu(dlp->slave, new_mtu);
}