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
struct rtl_coalesce_info {scalar_t__ speed; } ;
struct rtl8169_private {struct rtl_coalesce_info* coalesce_info; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int ELNRNG ; 
 struct rtl_coalesce_info const* ERR_PTR (int) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int phy_ethtool_get_link_ksettings (struct net_device*,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static const struct rtl_coalesce_info *rtl_coalesce_info(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	struct ethtool_link_ksettings ecmd;
	const struct rtl_coalesce_info *ci;
	int rc;

	rc = phy_ethtool_get_link_ksettings(dev, &ecmd);
	if (rc < 0)
		return ERR_PTR(rc);

	for (ci = tp->coalesce_info; ci->speed != 0; ci++) {
		if (ecmd.base.speed == ci->speed) {
			return ci;
		}
	}

	return ERR_PTR(-ELNRNG);
}