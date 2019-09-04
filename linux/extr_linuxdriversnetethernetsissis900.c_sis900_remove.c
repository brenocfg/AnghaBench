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
struct sis900_private {int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  tx_ring_dma; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  rx_ring; struct mii_phy* first_mii; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct mii_phy {struct mii_phy* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_TOTAL_SIZE ; 
 int /*<<< orphan*/  TX_TOTAL_SIZE ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct mii_phy*) ; 
 struct sis900_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void sis900_remove(struct pci_dev *pci_dev)
{
	struct net_device *net_dev = pci_get_drvdata(pci_dev);
	struct sis900_private *sis_priv = netdev_priv(net_dev);

	unregister_netdev(net_dev);

	while (sis_priv->first_mii) {
		struct mii_phy *phy = sis_priv->first_mii;

		sis_priv->first_mii = phy->next;
		kfree(phy);
	}

	pci_free_consistent(pci_dev, RX_TOTAL_SIZE, sis_priv->rx_ring,
		sis_priv->rx_ring_dma);
	pci_free_consistent(pci_dev, TX_TOTAL_SIZE, sis_priv->tx_ring,
		sis_priv->tx_ring_dma);
	pci_iounmap(pci_dev, sis_priv->ioaddr);
	free_netdev(net_dev);
	pci_release_regions(pci_dev);
}