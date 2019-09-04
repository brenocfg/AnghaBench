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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_ch_napi (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  dpni_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpni_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ drain_ingress_frames (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  drain_pool (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,scalar_t__) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 

__attribute__((used)) static int dpaa2_eth_stop(struct net_device *net_dev)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	int dpni_enabled;
	int retries = 10;
	u32 drained;

	netif_tx_stop_all_queues(net_dev);
	netif_carrier_off(net_dev);

	/* Loop while dpni_disable() attempts to drain the egress FQs
	 * and confirm them back to us.
	 */
	do {
		dpni_disable(priv->mc_io, 0, priv->mc_token);
		dpni_is_enabled(priv->mc_io, 0, priv->mc_token, &dpni_enabled);
		if (dpni_enabled)
			/* Allow the hardware some slack */
			msleep(100);
	} while (dpni_enabled && --retries);
	if (!retries) {
		netdev_warn(net_dev, "Retry count exceeded disabling DPNI\n");
		/* Must go on and disable NAPI nonetheless, so we don't crash at
		 * the next "ifconfig up"
		 */
	}

	/* Wait for NAPI to complete on every core and disable it.
	 * In particular, this will also prevent NAPI from being rescheduled if
	 * a new CDAN is serviced, effectively discarding the CDAN. We therefore
	 * don't even need to disarm the channels, except perhaps for the case
	 * of a huge coalescing value.
	 */
	disable_ch_napi(priv);

	 /* Manually drain the Rx and TxConf queues */
	drained = drain_ingress_frames(priv);
	if (drained)
		netdev_dbg(net_dev, "Drained %d frames.\n", drained);

	/* Empty the buffer pool */
	drain_pool(priv);

	return 0;
}