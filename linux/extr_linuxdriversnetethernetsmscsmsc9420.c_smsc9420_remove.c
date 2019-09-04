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
struct smsc9420_pdata {int tx_buffers; int rx_buffers; scalar_t__ ioaddr; int /*<<< orphan*/  rx_dma_addr; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; } ;
struct smsc9420_dma_desc {int dummy; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ LAN9420_CPSR_ENDIAN_OFFSET ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void smsc9420_remove(struct pci_dev *pdev)
{
	struct net_device *dev;
	struct smsc9420_pdata *pd;

	dev = pci_get_drvdata(pdev);
	if (!dev)
		return;

	pd = netdev_priv(dev);
	unregister_netdev(dev);

	/* tx_buffers and rx_buffers are freed in stop */
	BUG_ON(pd->tx_buffers);
	BUG_ON(pd->rx_buffers);

	BUG_ON(!pd->tx_ring);
	BUG_ON(!pd->rx_ring);

	pci_free_consistent(pdev, sizeof(struct smsc9420_dma_desc) *
		(RX_RING_SIZE + TX_RING_SIZE), pd->rx_ring, pd->rx_dma_addr);

	iounmap(pd->ioaddr - LAN9420_CPSR_ENDIAN_OFFSET);
	pci_release_regions(pdev);
	free_netdev(dev);
	pci_disable_device(pdev);
}