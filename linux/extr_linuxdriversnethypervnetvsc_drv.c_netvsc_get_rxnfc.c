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
typedef  int /*<<< orphan*/  u32 ;
struct netvsc_device {int /*<<< orphan*/  num_chn; } ;
struct net_device_context {int /*<<< orphan*/  nvdev; } ;
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENODEV ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int netvsc_get_rss_hash_opts (struct net_device_context*,struct ethtool_rxnfc*) ; 
 struct netvsc_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netvsc_get_rxnfc(struct net_device *dev, struct ethtool_rxnfc *info,
		 u32 *rules)
{
	struct net_device_context *ndc = netdev_priv(dev);
	struct netvsc_device *nvdev = rtnl_dereference(ndc->nvdev);

	if (!nvdev)
		return -ENODEV;

	switch (info->cmd) {
	case ETHTOOL_GRXRINGS:
		info->data = nvdev->num_chn;
		return 0;

	case ETHTOOL_GRXFH:
		return netvsc_get_rss_hash_opts(ndc, info);
	}
	return -EOPNOTSUPP;
}