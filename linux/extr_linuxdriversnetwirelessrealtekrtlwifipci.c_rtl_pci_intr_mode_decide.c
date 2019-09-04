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
struct rtl_pci_priv {int dummy; } ;
struct rtl_pci {scalar_t__ msi_support; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int rtl_pci_intr_mode_legacy (struct ieee80211_hw*) ; 
 int rtl_pci_intr_mode_msi (struct ieee80211_hw*) ; 
 struct rtl_pci* rtl_pcidev (struct rtl_pci_priv*) ; 
 struct rtl_pci_priv* rtl_pcipriv (struct ieee80211_hw*) ; 

__attribute__((used)) static int rtl_pci_intr_mode_decide(struct ieee80211_hw *hw)
{
	struct rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(pcipriv);
	int ret;

	if (rtlpci->msi_support) {
		ret = rtl_pci_intr_mode_msi(hw);
		if (ret < 0)
			ret = rtl_pci_intr_mode_legacy(hw);
	} else {
		ret = rtl_pci_intr_mode_legacy(hw);
	}
	return ret;
}