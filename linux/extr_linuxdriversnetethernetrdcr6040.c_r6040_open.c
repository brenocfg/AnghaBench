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
struct r6040_private {int /*<<< orphan*/  rx_ring_dma; void* rx_ring; int /*<<< orphan*/  pdev; int /*<<< orphan*/  tx_ring_dma; void* tx_ring; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  RX_DESC_SIZE ; 
 int /*<<< orphan*/  TX_DESC_SIZE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct r6040_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r6040_interrupt ; 
 int /*<<< orphan*/  r6040_mac_address (struct net_device*) ; 
 int r6040_up (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int r6040_open(struct net_device *dev)
{
	struct r6040_private *lp = netdev_priv(dev);
	int ret;

	/* Request IRQ and Register interrupt handler */
	ret = request_irq(dev->irq, r6040_interrupt,
		IRQF_SHARED, dev->name, dev);
	if (ret)
		goto out;

	/* Set MAC address */
	r6040_mac_address(dev);

	/* Allocate Descriptor memory */
	lp->rx_ring =
		pci_alloc_consistent(lp->pdev, RX_DESC_SIZE, &lp->rx_ring_dma);
	if (!lp->rx_ring) {
		ret = -ENOMEM;
		goto err_free_irq;
	}

	lp->tx_ring =
		pci_alloc_consistent(lp->pdev, TX_DESC_SIZE, &lp->tx_ring_dma);
	if (!lp->tx_ring) {
		ret = -ENOMEM;
		goto err_free_rx_ring;
	}

	ret = r6040_up(dev);
	if (ret)
		goto err_free_tx_ring;

	napi_enable(&lp->napi);
	netif_start_queue(dev);

	return 0;

err_free_tx_ring:
	pci_free_consistent(lp->pdev, TX_DESC_SIZE, lp->tx_ring,
			lp->tx_ring_dma);
err_free_rx_ring:
	pci_free_consistent(lp->pdev, RX_DESC_SIZE, lp->rx_ring,
			lp->rx_ring_dma);
err_free_irq:
	free_irq(dev->irq, dev);
out:
	return ret;
}