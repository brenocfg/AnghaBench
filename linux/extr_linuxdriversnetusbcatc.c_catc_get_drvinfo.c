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
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct catc {int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_VERSION ; 
 int /*<<< orphan*/  driver_name ; 
 struct catc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void catc_get_drvinfo(struct net_device *dev,
			     struct ethtool_drvinfo *info)
{
	struct catc *catc = netdev_priv(dev);
	strlcpy(info->driver, driver_name, sizeof(info->driver));
	strlcpy(info->version, DRIVER_VERSION, sizeof(info->version));
	usb_make_path(catc->usbdev, info->bus_info, sizeof(info->bus_info));
}