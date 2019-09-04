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
struct pci_dev {int dummy; } ;
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {int rx_ring_size; int tx_ring_size; int /*<<< orphan*/  map; int /*<<< orphan*/  eeprom; int /*<<< orphan*/  rx_buffers; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  rx_ring; } ;
struct adm8211_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void adm8211_remove(struct pci_dev *pdev)
{
	struct ieee80211_hw *dev = pci_get_drvdata(pdev);
	struct adm8211_priv *priv;

	if (!dev)
		return;

	ieee80211_unregister_hw(dev);

	priv = dev->priv;

	pci_free_consistent(pdev,
			    sizeof(struct adm8211_desc) * priv->rx_ring_size +
			    sizeof(struct adm8211_desc) * priv->tx_ring_size,
			    priv->rx_ring, priv->rx_ring_dma);

	kfree(priv->rx_buffers);
	kfree(priv->eeprom);
	pci_iounmap(pdev, priv->map);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	ieee80211_free_hw(dev);
}