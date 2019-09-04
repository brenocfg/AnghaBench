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
struct stmmac_priv {int irq_wake; int oldlink; int /*<<< orphan*/  oldduplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  lock; TYPE_1__* plat; int /*<<< orphan*/  device; int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  wolopts; int /*<<< orphan*/  hw; } ;
struct net_device {scalar_t__ phydev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stmmac_clk; int /*<<< orphan*/  pclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_disable_all_queues (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_mac_set (struct stmmac_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stmmac_pmt (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_stop_all_dma (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_stop_all_queues (struct stmmac_priv*) ; 

int stmmac_suspend(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct stmmac_priv *priv = netdev_priv(ndev);

	if (!ndev || !netif_running(ndev))
		return 0;

	if (ndev->phydev)
		phy_stop(ndev->phydev);

	mutex_lock(&priv->lock);

	netif_device_detach(ndev);
	stmmac_stop_all_queues(priv);

	stmmac_disable_all_queues(priv);

	/* Stop TX/RX DMA */
	stmmac_stop_all_dma(priv);

	/* Enable Power down mode by programming the PMT regs */
	if (device_may_wakeup(priv->device)) {
		stmmac_pmt(priv, priv->hw, priv->wolopts);
		priv->irq_wake = 1;
	} else {
		stmmac_mac_set(priv, priv->ioaddr, false);
		pinctrl_pm_select_sleep_state(priv->device);
		/* Disable clock in case of PWM is off */
		clk_disable(priv->plat->pclk);
		clk_disable(priv->plat->stmmac_clk);
	}
	mutex_unlock(&priv->lock);

	priv->oldlink = false;
	priv->speed = SPEED_UNKNOWN;
	priv->oldduplex = DUPLEX_UNKNOWN;
	return 0;
}