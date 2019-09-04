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
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath5k_hw {int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath5k_deinit_ah (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ieee80211_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath5k_pci_remove(struct pci_dev *pdev)
{
	struct ieee80211_hw *hw = pci_get_drvdata(pdev);
	struct ath5k_hw *ah = hw->priv;

	ath5k_deinit_ah(ah);
	pci_iounmap(pdev, ah->iobase);
	pci_release_region(pdev, 0);
	pci_disable_device(pdev);
	ieee80211_free_hw(hw);
}