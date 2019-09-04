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
struct phy_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct axienet_local {int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_err_tasklet; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  phy_mode; scalar_t__ phy_node; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int XAE_MDIO_MC_MDIOEN_MASK ; 
 int /*<<< orphan*/  XAE_MDIO_MC_OFFSET ; 
 int /*<<< orphan*/  axienet_adjust_link ; 
 int /*<<< orphan*/  axienet_device_reset (struct net_device*) ; 
 int /*<<< orphan*/  axienet_dma_err_handler ; 
 int axienet_ior (struct axienet_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axienet_iow (struct axienet_local*,int /*<<< orphan*/ ,int) ; 
 int axienet_mdio_wait_until_ready (struct axienet_local*) ; 
 int /*<<< orphan*/  axienet_rx_irq ; 
 int /*<<< orphan*/  axienet_tx_irq ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 
 struct phy_device* of_phy_connect (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int axienet_open(struct net_device *ndev)
{
	int ret, mdio_mcreg;
	struct axienet_local *lp = netdev_priv(ndev);
	struct phy_device *phydev = NULL;

	dev_dbg(&ndev->dev, "axienet_open()\n");

	mdio_mcreg = axienet_ior(lp, XAE_MDIO_MC_OFFSET);
	ret = axienet_mdio_wait_until_ready(lp);
	if (ret < 0)
		return ret;
	/* Disable the MDIO interface till Axi Ethernet Reset is completed.
	 * When we do an Axi Ethernet reset, it resets the complete core
	 * including the MDIO. If MDIO is not disabled when the reset
	 * process is started, MDIO will be broken afterwards.
	 */
	axienet_iow(lp, XAE_MDIO_MC_OFFSET,
		    (mdio_mcreg & (~XAE_MDIO_MC_MDIOEN_MASK)));
	axienet_device_reset(ndev);
	/* Enable the MDIO */
	axienet_iow(lp, XAE_MDIO_MC_OFFSET, mdio_mcreg);
	ret = axienet_mdio_wait_until_ready(lp);
	if (ret < 0)
		return ret;

	if (lp->phy_node) {
		phydev = of_phy_connect(lp->ndev, lp->phy_node,
					axienet_adjust_link, 0, lp->phy_mode);

		if (!phydev)
			dev_err(lp->dev, "of_phy_connect() failed\n");
		else
			phy_start(phydev);
	}

	/* Enable tasklets for Axi DMA error handling */
	tasklet_init(&lp->dma_err_tasklet, axienet_dma_err_handler,
		     (unsigned long) lp);

	/* Enable interrupts for Axi DMA Tx */
	ret = request_irq(lp->tx_irq, axienet_tx_irq, 0, ndev->name, ndev);
	if (ret)
		goto err_tx_irq;
	/* Enable interrupts for Axi DMA Rx */
	ret = request_irq(lp->rx_irq, axienet_rx_irq, 0, ndev->name, ndev);
	if (ret)
		goto err_rx_irq;

	return 0;

err_rx_irq:
	free_irq(lp->tx_irq, ndev);
err_tx_irq:
	if (phydev)
		phy_disconnect(phydev);
	tasklet_kill(&lp->dma_err_tasklet);
	dev_err(lp->dev, "request_irq() failed\n");
	return ret;
}