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
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  data; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  rx_hash_fields; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 int /*<<< orphan*/  dpaa2_eth_queue_count (struct dpaa2_eth_priv*) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dpaa2_eth_get_rxnfc(struct net_device *net_dev,
			       struct ethtool_rxnfc *rxnfc, u32 *rule_locs)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);

	switch (rxnfc->cmd) {
	case ETHTOOL_GRXFH:
		/* we purposely ignore cmd->flow_type for now, because the
		 * classifier only supports a single set of fields for all
		 * protocols
		 */
		rxnfc->data = priv->rx_hash_fields;
		break;
	case ETHTOOL_GRXRINGS:
		rxnfc->data = dpaa2_eth_queue_count(priv);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}