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
struct tun_struct {int flags; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* DRV_NAME ; 
 char* DRV_VERSION ; 
#define  IFF_TAP 129 
#define  IFF_TUN 128 
 int TUN_TYPE_MASK ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void tun_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct tun_struct *tun = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, sizeof(info->driver));
	strlcpy(info->version, DRV_VERSION, sizeof(info->version));

	switch (tun->flags & TUN_TYPE_MASK) {
	case IFF_TUN:
		strlcpy(info->bus_info, "tun", sizeof(info->bus_info));
		break;
	case IFF_TAP:
		strlcpy(info->bus_info, "tap", sizeof(info->bus_info));
		break;
	}
}