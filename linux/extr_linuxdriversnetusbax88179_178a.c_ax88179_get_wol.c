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
typedef  int u8 ;
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int supported; int wolopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_ACCESS_MAC ; 
 int /*<<< orphan*/  AX_MONITOR_MOD ; 
 int AX_MONITOR_MODE_RWLC ; 
 int AX_MONITOR_MODE_RWMP ; 
 int WAKE_MAGIC ; 
 int WAKE_PHY ; 
 scalar_t__ ax88179_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
ax88179_get_wol(struct net_device *net, struct ethtool_wolinfo *wolinfo)
{
	struct usbnet *dev = netdev_priv(net);
	u8 opt;

	if (ax88179_read_cmd(dev, AX_ACCESS_MAC, AX_MONITOR_MOD,
			     1, 1, &opt) < 0) {
		wolinfo->supported = 0;
		wolinfo->wolopts = 0;
		return;
	}

	wolinfo->supported = WAKE_PHY | WAKE_MAGIC;
	wolinfo->wolopts = 0;
	if (opt & AX_MONITOR_MODE_RWLC)
		wolinfo->wolopts |= WAKE_PHY;
	if (opt & AX_MONITOR_MODE_RWMP)
		wolinfo->wolopts |= WAKE_MAGIC;
}