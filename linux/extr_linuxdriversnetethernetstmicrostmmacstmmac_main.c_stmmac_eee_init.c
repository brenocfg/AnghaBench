#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ eee; } ;
struct stmmac_priv {int tx_lpi_timer; int eee_active; struct net_device* dev; int /*<<< orphan*/  lock; TYPE_3__* hw; int /*<<< orphan*/  eee_ctrl_timer; TYPE_2__ dma_cap; TYPE_1__* plat; } ;
struct net_device {TYPE_5__* phydev; } ;
struct TYPE_9__ {int /*<<< orphan*/  link; } ;
struct TYPE_8__ {scalar_t__ pcs; } ;
struct TYPE_6__ {int interface; } ;

/* Variables and functions */
 int PHY_INTERFACE_MODE_GMII ; 
 int PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  STMMAC_DEFAULT_LIT_LS ; 
 int /*<<< orphan*/  STMMAC_LPI_T (int /*<<< orphan*/ ) ; 
 scalar_t__ STMMAC_PCS_RGMII ; 
 scalar_t__ STMMAC_PCS_RTBI ; 
 scalar_t__ STMMAC_PCS_TBI ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eee_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 scalar_t__ phy_init_eee (TYPE_5__*,int) ; 
 int /*<<< orphan*/  phy_interface_mode_is_rgmii (int) ; 
 int /*<<< orphan*/  stmmac_eee_ctrl_timer ; 
 int /*<<< orphan*/  stmmac_set_eee_pls (struct stmmac_priv*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_set_eee_timer (struct stmmac_priv*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool stmmac_eee_init(struct stmmac_priv *priv)
{
	struct net_device *ndev = priv->dev;
	int interface = priv->plat->interface;
	bool ret = false;

	if ((interface != PHY_INTERFACE_MODE_MII) &&
	    (interface != PHY_INTERFACE_MODE_GMII) &&
	    !phy_interface_mode_is_rgmii(interface))
		goto out;

	/* Using PCS we cannot dial with the phy registers at this stage
	 * so we do not support extra feature like EEE.
	 */
	if ((priv->hw->pcs == STMMAC_PCS_RGMII) ||
	    (priv->hw->pcs == STMMAC_PCS_TBI) ||
	    (priv->hw->pcs == STMMAC_PCS_RTBI))
		goto out;

	/* MAC core supports the EEE feature. */
	if (priv->dma_cap.eee) {
		int tx_lpi_timer = priv->tx_lpi_timer;

		/* Check if the PHY supports EEE */
		if (phy_init_eee(ndev->phydev, 1)) {
			/* To manage at run-time if the EEE cannot be supported
			 * anymore (for example because the lp caps have been
			 * changed).
			 * In that case the driver disable own timers.
			 */
			mutex_lock(&priv->lock);
			if (priv->eee_active) {
				netdev_dbg(priv->dev, "disable EEE\n");
				del_timer_sync(&priv->eee_ctrl_timer);
				stmmac_set_eee_timer(priv, priv->hw, 0,
						tx_lpi_timer);
			}
			priv->eee_active = 0;
			mutex_unlock(&priv->lock);
			goto out;
		}
		/* Activate the EEE and start timers */
		mutex_lock(&priv->lock);
		if (!priv->eee_active) {
			priv->eee_active = 1;
			timer_setup(&priv->eee_ctrl_timer,
				    stmmac_eee_ctrl_timer, 0);
			mod_timer(&priv->eee_ctrl_timer,
				  STMMAC_LPI_T(eee_timer));

			stmmac_set_eee_timer(priv, priv->hw,
					STMMAC_DEFAULT_LIT_LS, tx_lpi_timer);
		}
		/* Set HW EEE according to the speed */
		stmmac_set_eee_pls(priv, priv->hw, ndev->phydev->link);

		ret = true;
		mutex_unlock(&priv->lock);

		netdev_dbg(priv->dev, "Energy-Efficient Ethernet initialized\n");
	}
out:
	return ret;
}