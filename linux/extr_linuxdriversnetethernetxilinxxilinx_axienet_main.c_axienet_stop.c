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
typedef  int u32 ;
struct net_device {scalar_t__ phydev; int /*<<< orphan*/  dev; } ;
struct axienet_local {int options; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  dma_err_tasklet; } ;

/* Variables and functions */
 int XAE_OPTION_RXEN ; 
 int XAE_OPTION_TXEN ; 
 int XAXIDMA_CR_RUNSTOP_MASK ; 
 int /*<<< orphan*/  XAXIDMA_RX_CR_OFFSET ; 
 int /*<<< orphan*/  XAXIDMA_TX_CR_OFFSET ; 
 int /*<<< orphan*/  axienet_dma_bd_release (struct net_device*) ; 
 int axienet_dma_in32 (struct axienet_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axienet_dma_out32 (struct axienet_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  axienet_setoptions (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int axienet_stop(struct net_device *ndev)
{
	u32 cr;
	struct axienet_local *lp = netdev_priv(ndev);

	dev_dbg(&ndev->dev, "axienet_close()\n");

	cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET,
			  cr & (~XAXIDMA_CR_RUNSTOP_MASK));
	cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET,
			  cr & (~XAXIDMA_CR_RUNSTOP_MASK));
	axienet_setoptions(ndev, lp->options &
			   ~(XAE_OPTION_TXEN | XAE_OPTION_RXEN));

	tasklet_kill(&lp->dma_err_tasklet);

	free_irq(lp->tx_irq, ndev);
	free_irq(lp->rx_irq, ndev);

	if (ndev->phydev)
		phy_disconnect(ndev->phydev);

	axienet_dma_bd_release(ndev);
	return 0;
}