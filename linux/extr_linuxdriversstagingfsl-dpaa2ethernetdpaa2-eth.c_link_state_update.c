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
struct dpni_link_state {scalar_t__ up; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  net_dev; struct dpni_link_state link_state; int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int dpni_get_link_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_link_state*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int link_state_update(struct dpaa2_eth_priv *priv)
{
	struct dpni_link_state state;
	int err;

	err = dpni_get_link_state(priv->mc_io, 0, priv->mc_token, &state);
	if (unlikely(err)) {
		netdev_err(priv->net_dev,
			   "dpni_get_link_state() failed\n");
		return err;
	}

	/* Chech link state; speed / duplex changes are not treated yet */
	if (priv->link_state.up == state.up)
		return 0;

	priv->link_state = state;
	if (state.up) {
		netif_carrier_on(priv->net_dev);
		netif_tx_start_all_queues(priv->net_dev);
	} else {
		netif_tx_stop_all_queues(priv->net_dev);
		netif_carrier_off(priv->net_dev);
	}

	netdev_info(priv->net_dev, "Link Event: state %s\n",
		    state.up ? "up" : "down");

	return 0;
}