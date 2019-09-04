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
struct ethsw_port_priv {int link_state; int /*<<< orphan*/  idx; TYPE_1__* ethsw_data; } ;
struct dpsw_link_state {int up; } ;
struct TYPE_2__ {int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int dpsw_if_get_link_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpsw_link_state*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static int port_carrier_state_sync(struct net_device *netdev)
{
	struct ethsw_port_priv *port_priv = netdev_priv(netdev);
	struct dpsw_link_state state;
	int err;

	err = dpsw_if_get_link_state(port_priv->ethsw_data->mc_io, 0,
				     port_priv->ethsw_data->dpsw_handle,
				     port_priv->idx, &state);
	if (err) {
		netdev_err(netdev, "dpsw_if_get_link_state() err %d\n", err);
		return err;
	}

	WARN_ONCE(state.up > 1, "Garbage read into link_state");

	if (state.up != port_priv->link_state) {
		if (state.up)
			netif_carrier_on(netdev);
		else
			netif_carrier_off(netdev);
		port_priv->link_state = state.up;
	}
	return 0;
}