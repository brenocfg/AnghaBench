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
struct vnet {int nports; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int NUM_VNET_PORT_STATS ; 
 int /*<<< orphan*/  ethtool_stats_keys ; 
 scalar_t__ netdev_priv (struct net_device*) ; 

__attribute__((used)) static int vnet_get_sset_count(struct net_device *dev, int sset)
{
	struct vnet *vp = (struct vnet *)netdev_priv(dev);

	switch (sset) {
	case ETH_SS_STATS:
		return ARRAY_SIZE(ethtool_stats_keys)
			+ (NUM_VNET_PORT_STATS * vp->nports);
	default:
		return -EOPNOTSUPP;
	}
}