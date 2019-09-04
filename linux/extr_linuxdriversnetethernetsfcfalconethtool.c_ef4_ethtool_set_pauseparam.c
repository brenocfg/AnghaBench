#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct ef4_nic {scalar_t__ link_advertising; int wanted_fc; int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  net_dev; TYPE_2__* phy_op; TYPE_1__* type; } ;
struct TYPE_4__ {int (* reconfigure ) (struct ef4_nic*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* prepare_enable_fc_tx ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int EF4_FC_AUTO ; 
 int EF4_FC_RX ; 
 int EF4_FC_TX ; 
 int EINVAL ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ef4_link_set_wanted_fc (struct ef4_nic*,int) ; 
 int /*<<< orphan*/  ef4_mac_reconfigure (struct ef4_nic*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 
 int stub2 (struct ef4_nic*) ; 

__attribute__((used)) static int ef4_ethtool_set_pauseparam(struct net_device *net_dev,
				      struct ethtool_pauseparam *pause)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	u8 wanted_fc, old_fc;
	u32 old_adv;
	int rc = 0;

	mutex_lock(&efx->mac_lock);

	wanted_fc = ((pause->rx_pause ? EF4_FC_RX : 0) |
		     (pause->tx_pause ? EF4_FC_TX : 0) |
		     (pause->autoneg ? EF4_FC_AUTO : 0));

	if ((wanted_fc & EF4_FC_TX) && !(wanted_fc & EF4_FC_RX)) {
		netif_dbg(efx, drv, efx->net_dev,
			  "Flow control unsupported: tx ON rx OFF\n");
		rc = -EINVAL;
		goto out;
	}

	if ((wanted_fc & EF4_FC_AUTO) && !efx->link_advertising) {
		netif_dbg(efx, drv, efx->net_dev,
			  "Autonegotiation is disabled\n");
		rc = -EINVAL;
		goto out;
	}

	/* Hook for Falcon bug 11482 workaround */
	if (efx->type->prepare_enable_fc_tx &&
	    (wanted_fc & EF4_FC_TX) && !(efx->wanted_fc & EF4_FC_TX))
		efx->type->prepare_enable_fc_tx(efx);

	old_adv = efx->link_advertising;
	old_fc = efx->wanted_fc;
	ef4_link_set_wanted_fc(efx, wanted_fc);
	if (efx->link_advertising != old_adv ||
	    (efx->wanted_fc ^ old_fc) & EF4_FC_AUTO) {
		rc = efx->phy_op->reconfigure(efx);
		if (rc) {
			netif_err(efx, drv, efx->net_dev,
				  "Unable to advertise requested flow "
				  "control setting\n");
			goto out;
		}
	}

	/* Reconfigure the MAC. The PHY *may* generate a link state change event
	 * if the user just changed the advertised capabilities, but there's no
	 * harm doing this twice */
	ef4_mac_reconfigure(efx);

out:
	mutex_unlock(&efx->mac_lock);

	return rc;
}