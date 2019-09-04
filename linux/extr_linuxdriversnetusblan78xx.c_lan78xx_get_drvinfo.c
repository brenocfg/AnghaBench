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
struct lan78xx_net {int /*<<< orphan*/  udev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lan78xx_get_drvinfo(struct net_device *net,
				struct ethtool_drvinfo *info)
{
	struct lan78xx_net *dev = netdev_priv(net);

	strncpy(info->driver, DRIVER_NAME, sizeof(info->driver));
	usb_make_path(dev->udev, info->bus_info, sizeof(info->bus_info));
}