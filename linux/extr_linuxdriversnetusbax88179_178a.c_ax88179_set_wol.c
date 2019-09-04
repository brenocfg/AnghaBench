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
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_ACCESS_MAC ; 
 int /*<<< orphan*/  AX_MONITOR_MOD ; 
 int /*<<< orphan*/  AX_MONITOR_MODE_RWLC ; 
 int /*<<< orphan*/  AX_MONITOR_MODE_RWMP ; 
 int EINVAL ; 
 int WAKE_MAGIC ; 
 int WAKE_PHY ; 
 scalar_t__ ax88179_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
ax88179_set_wol(struct net_device *net, struct ethtool_wolinfo *wolinfo)
{
	struct usbnet *dev = netdev_priv(net);
	u8 opt = 0;

	if (wolinfo->wolopts & ~(WAKE_PHY | WAKE_MAGIC))
		return -EINVAL;

	if (wolinfo->wolopts & WAKE_PHY)
		opt |= AX_MONITOR_MODE_RWLC;
	if (wolinfo->wolopts & WAKE_MAGIC)
		opt |= AX_MONITOR_MODE_RWMP;

	if (ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_MONITOR_MOD,
			      1, 1, &opt) < 0)
		return -EINVAL;

	return 0;
}