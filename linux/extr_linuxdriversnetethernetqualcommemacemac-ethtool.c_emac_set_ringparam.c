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
struct ethtool_ringparam {int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;
struct emac_adapter {void* rx_desc_cnt; void* tx_desc_cnt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EMAC_MAX_RX_DESCS ; 
 int /*<<< orphan*/  EMAC_MAX_TX_DESCS ; 
 int /*<<< orphan*/  EMAC_MIN_RX_DESCS ; 
 int /*<<< orphan*/  EMAC_MIN_TX_DESCS ; 
 void* clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int emac_reinit_locked (struct emac_adapter*) ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int emac_set_ringparam(struct net_device *netdev,
			      struct ethtool_ringparam *ring)
{
	struct emac_adapter *adpt = netdev_priv(netdev);

	/* We don't have separate queues/rings for small/large frames, so
	 * reject any attempt to specify those values separately.
	 */
	if (ring->rx_mini_pending || ring->rx_jumbo_pending)
		return -EINVAL;

	adpt->tx_desc_cnt =
		clamp_val(ring->tx_pending, EMAC_MIN_TX_DESCS, EMAC_MAX_TX_DESCS);

	adpt->rx_desc_cnt =
		clamp_val(ring->rx_pending, EMAC_MIN_RX_DESCS, EMAC_MAX_RX_DESCS);

	if (netif_running(netdev))
		return emac_reinit_locked(adpt);

	return 0;
}