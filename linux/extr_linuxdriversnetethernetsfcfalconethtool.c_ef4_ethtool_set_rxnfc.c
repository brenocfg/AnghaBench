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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {int cmd; TYPE_1__ fs; } ;
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_FILTER_PRI_MANUAL ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 129 
#define  ETHTOOL_SRXCLSRLINS 128 
 int ef4_ethtool_set_class_rule (struct ef4_nic*,TYPE_1__*) ; 
 scalar_t__ ef4_filter_get_rx_id_limit (struct ef4_nic*) ; 
 int ef4_filter_remove_id_safe (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ef4_ethtool_set_rxnfc(struct net_device *net_dev,
				 struct ethtool_rxnfc *info)
{
	struct ef4_nic *efx = netdev_priv(net_dev);

	if (ef4_filter_get_rx_id_limit(efx) == 0)
		return -EOPNOTSUPP;

	switch (info->cmd) {
	case ETHTOOL_SRXCLSRLINS:
		return ef4_ethtool_set_class_rule(efx, &info->fs);

	case ETHTOOL_SRXCLSRLDEL:
		return ef4_filter_remove_id_safe(efx, EF4_FILTER_PRI_MANUAL,
						 info->fs.location);

	default:
		return -EOPNOTSUPP;
	}
}